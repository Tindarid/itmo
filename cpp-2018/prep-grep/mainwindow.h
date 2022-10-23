#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <QFutureWatcher>
#include <QTime>
#include <QCommonStyle>
#include <QThread>
#include <QTreeWidget>
#include <QDir>
#include "trigram.h"
#include "worker.h"

namespace Ui {
class MainWindow;
}

class main_window : public QMainWindow
{
    Q_OBJECT
    QThread workerThread;
    Worker* worker;

public:
    explicit main_window(QWidget *parent = 0);
    ~main_window();

private slots:
    void selectDirectory();
    static void scanDirectory(QString const&, QVector<TrigramSet>*);
    void indexDirectory();
    void showAboutDialog();
    void searchingFinished();
    void indexingFinished();
    void filteringFinished();
    void stopIndexing();
    void pauseIndexing();
    void patternChanged();
    void initSearch(QString const&);
    void handleResult(QString const&, QVector<QPair<QPair<int, int>, QString>>);
    void resolveSearch();
    void viewContents(QTreeWidgetItem*, int);

signals:
    void startSearching(QVector<TrigramSet> const& files, QString const& pattern);

private:
    std::unique_ptr<Ui::MainWindow> ui;
    QFutureWatcher<void> index;
    QFutureWatcher<void> find;
    QFutureWatcher<void> filter;
    QTime timer;
    QVector<TrigramSet> files;
    QCommonStyle style;
    QDir curdir;
};

#endif // MAINWINDOW_H
