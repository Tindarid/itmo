#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfo>
#include <QThread>
#include <QTime>
#include <QTreeWidgetItem>
#include <memory>

namespace Ui {
class MainWindow;
}

class main_window : public QMainWindow
{
    Q_OBJECT
    QThread searchThread;

public:
    explicit main_window(QWidget *parent = 0);
    ~main_window();

private:
    std::unique_ptr<Ui::MainWindow> ui;
    QTime timer;
    QString curDir;

public slots:
    void select_directory();
    void scan_directory(QString const& dir);
    void show_no_dups();
    void stopSearch();
    void show_about_dialog();
    void handleDups(QDir const&, QVector<QFileInfo>);
    void handleProgress(int);
    void enableFunctionality();
    void disableFunctionality();
    void onStart();
    void onFinish();
    void deleteSelected();
    void onItemClicked(QTreeWidgetItem*, int);

signals:
    void find_duplicates(QString const& dir);
};

#endif // MAINWINDOW_H
