#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "computing.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QLayout>
#include <QMessageBox>

using namespace std;

QVector<Computing> expressions;
QString newExpr1;
double abcde[5];

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("ОПЗ");
    newExpression = new addExpression();
    connect(newExpression, &addExpression::firstWindow, this, &MainWindow::show);
    GetAnotherExptessions();
    for (const auto& var : expressions) {
        ui->listWidget->addItem(var.getInfixExpression());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_showExpressions_clicked()
{
    QWidget *window = new QWidget();
        window->setWindowTitle("Результат преобразований и вычислений");
        window->setGeometry(QRect(430, 150, 800, 250));
        window->resize(650, 550);
        QTableWidget *tableWidget = new QTableWidget();
        QGridLayout *layout = new QGridLayout(window);
        layout->addWidget(tableWidget, 0, 0);

        tableWidget->setColumnCount(8);
        tableWidget->setShowGrid(true);

        QStringList headers1;
                headers1.append("Инфиксное выражение");
                headers1.append("Постфиксное выражение");
                headers1.append("a");
                headers1.append("b");
                headers1.append("c");
                headers1.append("d");
                headers1.append("e");
                headers1.append("Результат");
        tableWidget->setHorizontalHeaderLabels(headers1);

        tableWidget->setSelectionMode(QAbstractItemView::NoSelection);

        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

        for (int i = 0; i < expressions.size(); ++i) {
            tableWidget->insertRow(i);
            tableWidget->setItem(i, 0, new QTableWidgetItem(expressions[i].getInfixExpression()));
            tableWidget->setItem(i, 1, new QTableWidgetItem(expressions[i].getPostfixExpression()));
            tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(expressions[i].getValueA())));
            tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(expressions[i].getValueB())));
            tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(expressions[i].getValueC())));
            tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(expressions[i].getValueD())));
            tableWidget->setItem(i, 6, new QTableWidgetItem(QString::number(expressions[i].getValueE())));
            tableWidget->setItem(i, 7, new QTableWidgetItem(QString::number(expressions[i].computing())));
            tableWidget->resizeColumnsToContents();
        }

        window->show();
}

 bool result1 = true;

void MainWindow::on_pushButton_addExpression_clicked()
{
    addExpression wind;
    wind.setModal(true);
    wind.exec();
    //this->close();
    if(!result1) {
    Computing expr(newExpr1);
    expr.setVariables(abcde[0], abcde[1], abcde[2], abcde[3], abcde[4]);
    expressions.push_back(expr);
    ui->listWidget->addItem(expr.getInfixExpression());
    }

}

bool cmp(int a, int b) {
    if (a && !b)
        return true;
    else if (!a && b)
        return false;
    else if (a < b)
        return true;
    else
        return false;
}

 QPair<int, int> Brackets_is_correct(const QString& str) {
    stack<int> figureBrackets;
    stack<int> squareBrackets;
    stack<int> roundBrackets;
    char leftFigBrackets = '{', rightFigBrackets = '}';
    char leftSqrBrackets = '[', rightSqrBrackets = ']';
    char leftRoundBrackets = '(', rightRoundBrackets = ')';

    int indFigure;
    int indSquare;
    int indRound;
    bool err1 = false;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == leftFigBrackets)
            figureBrackets.push(i);
        else if (str[i] == rightFigBrackets) {
            if (figureBrackets.size() > 0)
                figureBrackets.pop();
            else {
                indFigure =  i + 1;
                err1 = true;
                break;
            }
        }
    }
    if (!err1 && figureBrackets.size() > 0) {
        while (figureBrackets.size() != 1) {
            figureBrackets.pop();
        }
        indFigure =  figureBrackets.top() + 1;
    }
    else if (!err1) {
        indFigure = 0;
    }

    bool err2 = false;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == leftSqrBrackets)
            squareBrackets.push(i);
        else if (str[i] == rightSqrBrackets) {
            if (squareBrackets.size() > 0)
                squareBrackets.pop();
            else {
                indSquare =  i + 1;
                err2 = true;
                break;
            }
        }
    }
    if (!err2 && squareBrackets.size() > 0) {
        while (squareBrackets.size() != 1) {
            squareBrackets.pop();
        }
        indSquare =  squareBrackets.top() + 1;
    }
    else if (!err2) {
        indSquare = 0;
    }
    bool err3 = false;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == leftRoundBrackets)
            roundBrackets.push(i);
        else if (str[i] == rightRoundBrackets) {
            if (roundBrackets.size() > 0)
                roundBrackets.pop();
            else {
                indRound =  i + 1;
                err3 = true;
                break;
            }
        }
    }
    if (!err3 && roundBrackets.size() > 0) {
        while (roundBrackets.size() != 1) {
            roundBrackets.pop();
        }
        indRound = roundBrackets.top() + 1;
    }
    else if (!err3) {
        indRound = 0;
    }

    int res;
    if (indFigure && indRound && indSquare) {
        res = 0;
    }
    else {
        res = min(min(indFigure, indRound, cmp), indSquare, cmp);
    }

    int row = 1;
    int col = 0;

    QPair<int, int> position;
    for (int i = 0; i < res; ++i) {
        if (str[i] == '\n') {
            row++;
            col = 0;
        }
        else col++;
        position.first = row;
        position.second = col;
    }
    return position;
 }

 void addExpression::on_pushButton_saveData_clicked()
 {
     QString newExpr = ui->newInfixExpr->text().trimmed();

            for (const auto& ch : newExpr) {
                if (ch != 'a' && ch != 'b' && ch != 'c' && ch != 'd' && ch != 'e' && ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != ')' && ch != '(') {
                    throw "Недопустимый формат выражения";
                }
            }
            newExpr1 = newExpr;
            abcde[0] = stod(ui->lineEdit_a->text().toStdString());
            abcde[1] = stod(ui->lineEdit_b->text().toStdString());
            abcde[2] = stod(ui->lineEdit_c->text().toStdString());
            abcde[3] = stod(ui->lineEdit_d->text().toStdString());
            abcde[4] = stod(ui->lineEdit_e->text().toStdString());
            QPair<int, int> brackets = Brackets_is_correct(newExpr);
            if (brackets.first || brackets.second) {
                QMessageBox::critical(this, "ERROR", "Данные введены неверно!\nПовторите ввод данных!");
            }
            else {
                result1 = false;
                emit firstWindow();
                this->close();
            }
 }
