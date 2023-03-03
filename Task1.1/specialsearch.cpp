#include "specialsearch.h"
#include "ui_specialsearch.h"

specialSearch::specialSearch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::specialSearch)
{
    ui->setupUi(this);
    this->setWindowTitle("Ввод параметров поиска");
}

specialSearch::~specialSearch()
{
    delete ui;
}

