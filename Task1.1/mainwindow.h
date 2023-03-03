#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "newindow.h"
#include "specialsearch.h"
#include "dialog.h"
#include <QMovie>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addNode_clicked();

    void on_showList_clicked();

    void on_chooseFile_clicked();

    void on_showSpecialList_clicked();

    void on_deleteNode_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_exit_clicked();

    void on_editNode_clicked();

    void on_searchNode_clicked();

private:
    Ui::MainWindow *ui;
    neWindow *window;
    specialSearch *pwindow;
    Dialog *pDialog;
    QMovie *movie;
};
#endif // MAINWINDOW_H
