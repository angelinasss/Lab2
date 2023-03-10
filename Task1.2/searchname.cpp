#include "searchname.h"
#include "ui_searchname.h"

searchname::searchname(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::searchname)
{
    ui->setupUi(this);
}

searchname::~searchname()
{
    delete ui;
}

