#ifndef INPUTSEARCHSALARY_H
#define INPUTSEARCHSALARY_H

#include <QDialog>

namespace Ui {
class inputSearchSalary;
}

class inputSearchSalary : public QDialog
{
    Q_OBJECT

public:
    explicit inputSearchSalary(QWidget *parent = nullptr);
    ~inputSearchSalary();

signals:
    firstWindow();

private slots:
    void on_pushButton_saveSalary_clicked();

private:
    Ui::inputSearchSalary *ui;
};

#endif // INPUTSEARCHSALARY_H
