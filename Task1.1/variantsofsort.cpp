#include "variantsofsort.h"
#include "ui_variantsofsort.h"

variantsOfSort::variantsOfSort(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::variantsOfSort)
{
    ui->setupUi(this);
    this->setWindowTitle("Выбор критерия сортировки");
}

variantsOfSort::~variantsOfSort()
{
    delete ui;
}
