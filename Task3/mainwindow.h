#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "addexpression.h"
#include "ui_addexpression.h"

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
    void on_pushButton_showExpressions_clicked();

    void on_pushButton_addExpression_clicked();

private:
    Ui::MainWindow *ui;
    addExpression *newExpression;

};
#endif // MAINWINDOW_H
