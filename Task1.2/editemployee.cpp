#include "editemployee.h"
#include "ui_editemployee.h"

editEmployee::editEmployee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editEmployee)
{
    ui->setupUi(this);
    this->setWindowTitle("Выбор списка сотрудников по заданному параметру");
    inputSalary = new inputSearchSalary();
    inputHours = new hoursParametr();
}

editEmployee::~editEmployee()
{
    delete ui;
}

