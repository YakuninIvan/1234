#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>

#include "storage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    Storage* _Storage;
    QStringListModel* _modelList;
    QStringListModel* _modelDetails;

private slots:
    void on_actionOpen_triggered();
    void onDataStorageLoaded();
    void on_pushButton_clicked();

    void on_listView_clicked(const QModelIndex &index);

    void on_addBtn_clicked();

    void on_actionSaveFile_triggered();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_actionHelp_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
