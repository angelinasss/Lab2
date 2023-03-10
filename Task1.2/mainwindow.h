#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "addnewemployee.h"
#include "ui_addnewemployee.h"
#include "searchname.h"
#include "ui_searchname.h"
#include <QListWidgetItem>
#include "editemployee.h"
#include "ui_editemployee.h"
#include "inputsearchsalary.h"
#include "ui_inputsearchsalary.h"
#include "hoursparametr.h"
#include "ui_hoursparametr.h"
#include "inputoverhours.h"
#include "ui_inputoverhours.h"

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
    void on_pushButton_addEmployee_clicked();

    void on_pushButton_showList_clicked();

    void on_pushButton_chooseFile_clicked();

    void on_pushButton_SearchFio_clicked();

    void on_pushButton_deleteEmloyee_clicked();

    void on_pushButton_exit_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_editEmloyee_clicked();

    void on_pushButton_showSpecialList_clicked();

    void on_pushButton_SortList_clicked();

private:
    Ui::MainWindow *ui;
    addNewEmployee *newEmployee;
    searchname *nameSearch;
    editEmployee *editWindow;
    inputSearchSalary *inputSalary;
    hoursParametr *inputHours;
    inputOverHours *sortChoose;
};
#endif // MAINWINDOW_H
