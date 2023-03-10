#ifndef EDITEMPLOYEE_H
#define EDITEMPLOYEE_H

#include <QDialog>
#include "inputsearchsalary.h"
#include "ui_inputsearchsalary.h"
#include "hoursparametr.h"
#include "ui_hoursparametr.h"

namespace Ui {
class editEmployee;
}

class editEmployee : public QDialog
{
    Q_OBJECT

public:
    explicit editEmployee(QWidget *parent = nullptr);
    ~editEmployee();

signals:
    firstWindow();

private slots:
    void on_pushButton_listSalary_clicked();

    void on_pushButton_listHours_clicked();

    void on_pushButton_listOverHours_clicked();

private:
    Ui::editEmployee *ui;
    inputSearchSalary *inputSalary;
    hoursParametr *inputHours;
};

#endif // EDITEMPLOYEE_H
