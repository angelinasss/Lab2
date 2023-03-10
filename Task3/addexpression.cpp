#include "addexpression.h"
#include "ui_addexpression.h"

addExpression::addExpression(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addExpression)
{
    ui->setupUi(this);
}

addExpression::~addExpression()
{
    delete ui;
}

