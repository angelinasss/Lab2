#include "addnewemployee.h"
#include "ui_addnewemployee.h"

addNewEmployee::addNewEmployee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addNewEmployee)
{
    ui->setupUi(this);
    this->setWindowTitle("Добавление сотрудника");
}

addNewEmployee::~addNewEmployee()
{
    delete ui;
}


void addNewEmployee::on_pushButton_exit_clicked()
{
    ui->lineEdit_name->clear();
    ui->lineEdit_surname->clear();
    ui->lineEdit_patrionymicName->clear();
    ui->lineEdit_tabelNumber->clear();
    ui->lineEdit_hoursWorked->clear();
    ui->lineEdit_rate->clear();
    this->close();
    emit firstWindow();
}

