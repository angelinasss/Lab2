#ifndef INPUTOVERHOURS_H
#define INPUTOVERHOURS_H

#include <QDialog>

namespace Ui {
class inputOverHours;
}

class inputOverHours : public QDialog
{
    Q_OBJECT

public:
    explicit inputOverHours(QWidget *parent = nullptr);
    ~inputOverHours();

signals:
    firstWindow();

private slots:
    void on_pushButton_searchSurname_clicked();

    void on_pushButton_searchName_clicked();

    void on_pushButton_searchWorkedHours_clicked();

    void on_pushButton_rate_clicked();

private:
    Ui::inputOverHours *ui;
};

#endif // INPUTOVERHOURS_H
