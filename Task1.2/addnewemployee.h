#ifndef ADDNEWEMPLOYEE_H
#define ADDNEWEMPLOYEE_H

#include <QDialog>

namespace Ui {
class addNewEmployee;
}

class addNewEmployee : public QDialog
{
    Q_OBJECT

public:
    explicit addNewEmployee(QWidget *parent = nullptr);
    ~addNewEmployee();

signals:
    firstWindow();

private slots:
    void on_pushButton_saveData_clicked();

    void on_pushButton_exit_clicked();

private:
    Ui::addNewEmployee *ui;
};

#endif // ADDNEWEMPLOYEE_H
