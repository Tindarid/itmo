#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "search.h"

#include <QCommonStyle>
#include <QDesktopWidget>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QDirIterator>
#include <QDesktopServices>

main_window::main_window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(), qApp->desktop()->availableGeometry()));

    ui->treeWidget->header()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->treeWidget->header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);

    QCommonStyle style;
    ui->actionScan_Directory->setIcon(style.standardIcon(QCommonStyle::SP_MediaPlay));
    ui->actionStop_Scanning->setIcon(style.standardIcon(QCommonStyle::SP_MediaStop));
    ui->actionDelete->setIcon(style.standardIcon(QCommonStyle::SP_DialogResetButton));
    ui->actionExit->setIcon(style.standardIcon(QCommonStyle::SP_DialogCloseButton));
    ui->actionAbout->setIcon(style.standardIcon(QCommonStyle::SP_DialogHelpButton));
    connect(ui->actionScan_Directory, &QAction::triggered, this, &main_window::select_directory);
    connect(ui->actionStop_Scanning, &QAction::triggered, this, &main_window::stopSearch);
    connect(ui->actionDelete, &QAction::triggered, this, &main_window::deleteSelected);
    connect(ui->actionExit, &QAction::triggered, this, &QWidget::close);
    connect(ui->actionAbout, &QAction::triggered, this, &main_window::show_about_dialog);
    connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(onItemClicked(QTreeWidgetItem*,int)));

    qRegisterMetaType<QDir>("QDir");
    qRegisterMetaType<QVector<QFileInfo>>("QVector<QFieInfo>");
    setWindowTitle(QString("DupSearch"));
    ui->actionStop_Scanning->setDisabled(true);
    ui->actionDelete->setDisabled(true);
}

main_window::~main_window() {
    searchThread.quit();
    searchThread.wait();
}

void main_window::onFinish() {
    ui->statusBar->showMessage(QString("Finished in ") + QString::number(timer.elapsed() / 1000.0) + QString(" sec"));
    if (ui->treeWidget->topLevelItem(0) == 0) {
        show_no_dups();
    }
    enableFunctionality();

    searchThread.quit();
    searchThread.wait();
}

void main_window::onStart() {
    timer.start();
    ui->statusBar->showMessage("Duplicates search ...");
    ui->treeWidget->clear();
    disableFunctionality();

    Search* search = new Search;
    search->moveToThread(&searchThread);
    connect(&searchThread, &QThread::finished, search, &QObject::deleteLater);
    connect(this, &main_window::find_duplicates, search, &Search::doSearch);
    connect(search, &Search::dupseq, this, &main_window::handleDups);
    connect(search, &Search::progressState, this, &main_window::handleProgress);
    connect(search, &Search::finished, this, &main_window::onFinish);

    searchThread.start();
}

void main_window::disableFunctionality() {
    ui->actionScan_Directory->setDisabled(true);
    ui->actionStop_Scanning->setDisabled(false);
    ui->actionDelete->setDisabled(true);
}

void main_window::enableFunctionality() {
    ui->actionScan_Directory->setDisabled(false);
    ui->actionStop_Scanning->setDisabled(true);
    ui->actionDelete->setDisabled(false);
}

void main_window::select_directory() {
    QString dir = QFileDialog::getExistingDirectory(this, "Select Directory for Scanning",
                                                    QString(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    scan_directory(dir);
    curDir = dir;
}

void main_window::scan_directory(QString const& dir) {
    onStart();
    setWindowTitle(QString("Duplicates in directory - %1").arg(dir));
    find_duplicates(dir);
}

void main_window::show_no_dups() {
     QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
     item->setText(0, "Found no duplicates");
     item->setFlags(Qt::ItemIsEnabled);
     ui->treeWidget->addTopLevelItem(item);
}

void main_window::handleDups(QDir const& dir, QVector<QFileInfo> duplicates) {
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
    item->setText(0, QString("Found ") + QString::number(duplicates.size()) + QString(" duplicates"));
    item->setText(1, QString::number(duplicates.front().size()) + QString(" bytes"));
    item->setFlags(Qt::ItemIsDragEnabled | Qt::ItemIsEnabled);
    for (QFileInfo dup : duplicates) {
       QTreeWidgetItem* childItem = new QTreeWidgetItem();
       childItem->setText(0, dir.relativeFilePath(dup.filePath()));
       item->addChild(childItem);
    }
    ui->treeWidget->addTopLevelItem(item);
}

void main_window::handleProgress(int progress) {
    ui->progressBar->setValue(progress);
}

void main_window::show_about_dialog() {
    QMessageBox::aboutQt(this);
}

void main_window::stopSearch() {
    searchThread.requestInterruption();
}

void main_window::deleteSelected() {
    auto list = ui->treeWidget->selectedItems();
    if (list.size() == 0) {
        return;
    }
    QMessageBox dialog;
    dialog.setWindowTitle("Confirm");
    dialog.setText("Delete selected files?");
    dialog.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    dialog.setDefaultButton(QMessageBox::Cancel);
    if (dialog.exec() == QMessageBox::Ok) {
        int amount = 0;
        for (auto it = list.begin(); it != list.end(); ++it) {
            if (QFile::remove(QDir(curDir).absoluteFilePath((*it)->text(0)))) {
                amount++;
                (*it)->setSelected(false);
                (*it)->setDisabled(true);
            }
        }
        QString message = QString("Succesfully deleted ") + QString::number(amount) + QString(" files. ");
        if (amount < list.size()) {
            message += QString("Cannot delete " + QString::number(list.size() - amount) + QString(" files"));
        }
        ui->statusBar->showMessage(message);
    }
}

void main_window::onItemClicked(QTreeWidgetItem* item, int col) {
    if (item->parent() != nullptr) {
        QString path = QDir(curDir).absoluteFilePath(item->text(col));
        QDesktopServices::openUrl(QUrl::fromLocalFile(path));
    }
}
