#include "inputsearchsalary.h"
#include "ui_inputsearchsalary.h"

inputSearchSalary::inputSearchSalary(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inputSearchSalary)
{
    ui->setupUi(this);
    this->setWindowTitle("Ввод заработной платы");
}

inputSearchSalary::~inputSearchSalary()
{
    delete ui;
}

