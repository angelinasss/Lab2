#ifndef HOURSPARAMETR_H
#define HOURSPARAMETR_H

#include <QDialog>

namespace Ui {
class hoursParametr;
}

class hoursParametr : public QDialog
{
    Q_OBJECT

public:
    explicit hoursParametr(QWidget *parent = nullptr);
    ~hoursParametr();

signals:
    firstWindow();

private slots:
    void on_pushButton_saveHours_clicked();

private:
    Ui::hoursParametr *ui;
};

#endif // HOURSPARAMETR_H
