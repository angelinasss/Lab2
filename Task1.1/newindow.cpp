#include "newindow.h"
#include "ui_newindow.h"

neWindow::neWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::neWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Добавление");
}

neWindow::~neWindow()
{
    delete ui;
}

void neWindow::on_exit_clicked()
{
    this->close();
    emit firstWindow();
}

