#ifndef ADDEXPRESSION_H
#define ADDEXPRESSION_H

#include <QDialog>

namespace Ui {
class addExpression;
}

class addExpression : public QDialog
{
    Q_OBJECT

public:
    explicit addExpression(QWidget *parent = nullptr);
    ~addExpression();

signals:
    firstWindow();

private slots:
    void on_pushButton_saveData_clicked();

private:
    Ui::addExpression *ui;
};

#endif // ADDEXPRESSION_H
