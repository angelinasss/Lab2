#include "hoursparametr.h"
#include "ui_hoursparametr.h"

hoursParametr::hoursParametr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::hoursParametr)
{
    ui->setupUi(this);
    this->setWindowTitle("Ввод количества проработанных часов");
}

hoursParametr::~hoursParametr()
{
    delete ui;
}

