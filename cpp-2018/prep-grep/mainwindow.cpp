#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QDirIterator>
#include <QtConcurrent/QtConcurrentMap>
#include <QtConcurrent/QtConcurrentFilter>
#include <QtConcurrent/QtConcurrentRun>

main_window::main_window(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(), qApp->desktop()->availableGeometry()));

    ui->treeWidget->header()->setSectionResizeMode(0, QHeaderView::Stretch);

    ui->actionIndex_Directory->setIcon(style.standardIcon(QCommonStyle::SP_DialogOpenButton));
    ui->actionToggle_indexing->setIcon(style.standardIcon(QCommonStyle::SP_MediaPause));
    ui->actionStop_indexing->setIcon(style.standardIcon(QCommonStyle::SP_MediaStop));
    ui->actionExit->setIcon(style.standardIcon(QCommonStyle::SP_DialogCloseButton));
    ui->actionAbout->setIcon(style.standardIcon(QCommonStyle::SP_DialogHelpButton));
    ui->entryBrowser->setHidden(true);
    ui->progress->setHidden(true);

    connect(ui->actionIndex_Directory, &QAction::triggered, this, &main_window::selectDirectory);
    connect(ui->actionStop_indexing, &QAction::triggered, this, &main_window::stopIndexing);
    connect(ui->actionToggle_indexing, &QAction::triggered, this, &main_window::pauseIndexing);
    connect(ui->actionExit, &QAction::triggered, this, &QWidget::close);
    connect(ui->actionAbout, &QAction::triggered, this, &main_window::showAboutDialog);
    connect(&index, &QFutureWatcher<void>::finished, this, &main_window::indexingFinished);
    connect(&index, &QFutureWatcher<void>::started, this->ui->progress, &QProgressBar::reset);
    connect(&find, &QFutureWatcher<void>::finished, this, &main_window::indexDirectory);
    connect(&filter, &QFutureWatcher<void>::finished, this, &main_window::filteringFinished);
    connect(ui->pattern, &QLineEdit::textChanged, this, &main_window::patternChanged);
    connect(ui->searchButton, &QPushButton::clicked, this, &main_window::resolveSearch);
    connect(ui->treeWidget, &QTreeWidget::itemActivated, this, &main_window::viewContents);

    setWindowTitle("Prep-Grep");

    qRegisterMetaType<QVector<TrigramSet>>("QVector<TrigramSet>");
    qRegisterMetaType<QVector<QPair<QPair<int, int>, QString>>>("QVector<QPair<QPair<int, int>, QString>>");
    workerThread.start();
    workerThread.quit();
    workerThread.wait();

}

main_window::~main_window() {
    workerThread.quit();
    workerThread.wait();
}

void main_window::viewContents(QTreeWidgetItem* item, int col) {
    if (!item->parent()) {
        return;
    }
    if (ui->entryBrowser->isHidden()) {
        ui->entryBrowser->setHidden(false);
    }
    ui->entryBrowser->setText(item->text(col).split("\n").back());
}

void main_window::resolveSearch() {
    QString text = ui->searchButton->text();
    if (text == "Stop") {
        workerThread.requestInterruption();
    } else {
        initSearch(ui->pattern->text());
    }
}

void main_window::patternChanged() {
    if (!ui->smartSearch->isChecked()) {
        return;
    }
    QString pattern = ui->pattern->text();
    ui->treeWidget->clear();
    if (pattern.length() > 2) {
        if (!workerThread.isFinished()) {
            worker->blockSignals(true);
            workerThread.quit();
            workerThread.wait();
        }
        initSearch(pattern);
    } else {
        ui->status->clear();
    }
}

void main_window::initSearch(QString const& pattern) {
    if (pattern.length() == 0) {
        return;
    }
    timer.start();
    ui->entries->display(0);
    ui->treeWidget->clear();
    ui->status->setText("Searching...");
    ui->searchButton->setText("Stop");
    ui->entryBrowser->setHidden(true);

    worker = new Worker;
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &main_window::startSearching, worker, &Worker::doSearch);
    connect(worker, &Worker::result, this, &main_window::handleResult);
    connect(worker, &Worker::searchingFinished, this, &main_window::searchingFinished);
    workerThread.start();

    emit startSearching(files, pattern);
}

void main_window::handleResult(QString const& filename, QVector<QPair<QPair<int, int>, QString>> entries) {
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
    int count = 0;
    for (auto it = entries.begin(); it != entries.end(); ++it) {
        QTreeWidgetItem* childItem = new QTreeWidgetItem(item);
        count += it->first.second;
        childItem->setText(0, QString("Line ") + QString::number(it->first.first)
                           + QString(", entries ") + QString::number(it->first.second)
                           + QString(": \n") + it->second);
        item->addChild(childItem);
    }
    item->setText(0, QString("Found ") + QString::number(count) +
                  QString(" entries in ") + curdir.relativeFilePath(filename));
    ui->entries->display(ui->entries->intValue() + count);
    ui->treeWidget->addTopLevelItem(item);
}

void main_window::searchingFinished() {
    ui->status->setText(QString("Search time: ") + QString::number(timer.elapsed() / 1000.0) + QString(" sec."));
    if (!ui->treeWidget->topLevelItem(0)) {
        QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
        item->setText(0, QString("No entries"));
        ui->treeWidget->addTopLevelItem(item);
    }
    ui->searchButton->setText("Search");
    workerThread.quit();
    workerThread.wait();
}

void main_window::stopIndexing() {
    index.cancel();
}

void main_window::pauseIndexing() {
    if (index.isPaused()) {
        ui->actionToggle_indexing->setIcon(style.standardIcon(QCommonStyle::SP_MediaPause));
    } else {
        ui->actionToggle_indexing->setIcon(style.standardIcon(QCommonStyle::SP_MediaPlay));
    }
    index.togglePaused();
}

void main_window::filteringFinished() {
    ui->status->setText(QString("Time: ") + QString::number(timer.elapsed() / 1000.0) +
                       QString("sec. Indexed files: " + QString::number(files.size()) + QString(".")));
    ui->progress->setHidden(true);
    ui->pattern->setDisabled(false);
    ui->actionIndex_Directory->setDisabled(false);
    ui->actionToggle_indexing->setDisabled(true);
    ui->actionStop_indexing->setDisabled(true);
    ui->searchButton->setDisabled(false);
    ui->pattern->setFocus();
}

void main_window::indexingFinished() {
    ui->status->setText("Filtering .. ");
    connect(&filter, &QFutureWatcher<void>::progressRangeChanged, this->ui->progress, &QProgressBar::setRange);
    connect(&filter, &QFutureWatcher<void>::progressValueChanged, this->ui->progress, &QProgressBar::setValue);
    filter.setFuture(QtConcurrent::filter(files, TrigramUtil::isText));
}

void main_window::selectDirectory() {
    if (!workerThread.isFinished()) {
        workerThread.quit();
        workerThread.wait();
    }
    QString dir = QFileDialog::getExistingDirectory(this, "Select Directory for Scanning",
                                                    QString(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (dir.length() == 0) {
        return;
    }

    curdir = QDir(dir);
    setWindowTitle(QString("Directory - %1").arg(dir));

    timer.start();
    ui->treeWidget->clear();
    ui->pattern->setDisabled(true);
    ui->pattern->clear();
    ui->progress->setHidden(false);
    ui->searchButton->setDisabled(true);
    ui->entries->display(0);
    ui->status->setText(QString("Searching for files ..."));
    ui->entryBrowser->setHidden(true);

    connect(&find, &QFutureWatcher<void>::progressRangeChanged, this->ui->progress, &QProgressBar::setRange);
    connect(&find, &QFutureWatcher<void>::progressValueChanged, this->ui->progress, &QProgressBar::setValue);
    find.setFuture(QtConcurrent::run(scanDirectory, dir, &files));
}

void main_window::scanDirectory(QString const& dir, QVector<TrigramSet>* files) {
    QDirIterator it(dir, QDir::Hidden | QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    files->clear();
    while (it.hasNext()) {
        files->push_back(TrigramSet(it.next()));
    }
}

void main_window::indexDirectory() {
    ui->status->setText(QString("Indexing ..."));
    ui->actionIndex_Directory->setDisabled(true);
    ui->actionToggle_indexing->setDisabled(false);
    ui->actionStop_indexing->setDisabled(false);
    connect(&index, &QFutureWatcher<void>::progressRangeChanged, this->ui->progress, &QProgressBar::setRange);
    connect(&index, &QFutureWatcher<void>::progressValueChanged, this->ui->progress, &QProgressBar::setValue);
    index.setFuture(QtConcurrent::map(files, &TrigramUtil::processFile));
}

void main_window::showAboutDialog() {
    QMessageBox::aboutQt(this);
}
