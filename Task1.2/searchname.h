#ifndef SEARCHNAME_H
#define SEARCHNAME_H

#include <QDialog>

namespace Ui {
class searchname;
}

class searchname : public QDialog
{
    Q_OBJECT

public:
    explicit searchname(QWidget *parent = nullptr);
    ~searchname();

signals:
    firstWindow();

private slots:
    void on_pushButton_searchSurname_clicked();

private:
    Ui::searchname *ui;
};

#endif // SEARCHNAME_H
