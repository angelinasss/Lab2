#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "Stack.cpp"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int check = 0;

void MainWindow::on_pushButton_chooseFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Открытие документа", "C:\\", "Текстовые файлы (*.txt);");

    QFile file(fileName);
    file.open(QIODevice::ReadOnly);

    if(file.size() == 0) {
       QMessageBox::critical(this, "ERROR", "Вы выбрали пустой файл!\nПовторите выбор файла!");
    }
    else {
        ui->pathFile->setText(fileName);
        QTextStream file1(&file);
        ui->textEdit->setText(file1.readAll());
        check++;
        file.close();
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

void MainWindow::on_pushButton_checkCode_clicked()
{
    if (check == 0) {
        QMessageBox::critical(this, "ERROR!", "Текстовое поле пусто! Заполните его и повторите действие!");
    }
    else {
    if (Brackets_is_correct(ui->textEdit->toPlainText()).first == 0 && Brackets_is_correct(ui->textEdit->toPlainText()).second == 0) {
            QMessageBox::information(this, "SUCCESS!", "Все скобки расставлены правильно");
        }
        else {
            QMessageBox::critical(this, "ERROR!", "Скобки расставлены некорректно. Строка: " + QString::number(Brackets_is_correct(ui->textEdit->toPlainText()).first) + ". Столбец: " + QString::number(Brackets_is_correct(ui->textEdit->toPlainText()).second));
        }
    }
}


void MainWindow::on_textEdit_textChanged()
{
    check++;
}

