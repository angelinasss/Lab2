#ifndef NEWINDOW_H
#define NEWINDOW_H
#include <QMainWindow>
#include <QDialog>
#include <QMovie>
namespace Ui {
class neWindow;
}

class neWindow : public QDialog
{
    Q_OBJECT

public:
    explicit neWindow(QWidget *parent = nullptr);
    ~neWindow();
    QMovie *movie;

signals:
    void firstWindow();

private slots:

    void on_exit_clicked();

    void on_saveData_clicked();

private:
    Ui::neWindow *ui;
};

#endif // NEWINDOW_H
