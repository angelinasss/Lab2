#include "inputoverhours.h"
#include "ui_inputoverhours.h"

inputOverHours::inputOverHours(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inputOverHours)
{
    ui->setupUi(this);
}

inputOverHours::~inputOverHours()
{
    delete ui;
}

