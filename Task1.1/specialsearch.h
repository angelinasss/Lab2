#ifndef SPECIALSEARCH_H
#define SPECIALSEARCH_H

#include <QDialog>


namespace Ui {
class specialSearch;
}

class specialSearch : public QDialog
{
    Q_OBJECT

public:
    explicit specialSearch(QWidget *parent = nullptr);
    ~specialSearch();

signals:
    void firstWindow();

private slots:
    void on_saveData_clicked();

private:
    Ui::specialSearch *ui;
};

#endif // SPECIALSEARCH_H
