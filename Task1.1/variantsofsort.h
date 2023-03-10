#ifndef VARIANTSOFSORT_H
#define VARIANTSOFSORT_H

#include <QDialog>

namespace Ui {
class variantsOfSort;
}

class variantsOfSort : public QDialog
{
    Q_OBJECT

public:
    explicit variantsOfSort(QWidget *parent = nullptr);
    ~variantsOfSort();

signals:
    void firstWindow();

private slots:
    void on_dateSort_clicked();

    void on_TimeSort_clicked();

    void on_destinationSort_clicked();

    void on_seatsSort_clicked();

private:
    Ui::variantsOfSort *ui;
};

#endif // VARIANTSOFSORT_H
