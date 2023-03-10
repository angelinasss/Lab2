#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "traintimetable.h"
#include "List.cpp"
#include "ui_newindow.h"
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <QFile>
#include <QByteArray>
#include <string>
#include <algorithm>
#include <QFileDialog>
#include <QTime>
#include "specialsearch.h"
#include "ui_specialsearch.h"
#include "dialog.h"
#include "ui_dialog.h"
#include "mergeSort.cpp"
#include "variantsofsort.h"
#include "ui_variantsofsort.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->hide();
    ui->delete_reis->hide();
    ui->exit->hide();
    ui->edit_reis->hide();
    this->setWindowTitle("Главная");
    movie = new QMovie("C:\\Users\\Angelina\\Pictures\\Screenshots\\TnNs.gif");
    ui->picture->setMovie(movie);
    ui->picture->show();
    movie->start();
    window = new neWindow();
    pwindow = new specialSearch();
    pDialog = new Dialog();
    critSort = new variantsOfSort();
    connect(critSort, &variantsOfSort::firstWindow, this, &MainWindow::show);
    connect(pDialog, &Dialog::firstWindow, this, &MainWindow::show);
    connect(window, &neWindow::firstWindow, this, &MainWindow::show);
    connect(pwindow, &specialSearch::firstWindow, this, &MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}

List<TrainTimetable> trainsList;
QString fileName = "C:\\FilesForQtLabs\\trains.txt";
int counter = 0, indexx = 0, criteriaOfSort;
bool res = true;

void MainWindow::on_addNode_clicked()
{
    window->show();
    this->close();
}

void neWindow::on_saveData_clicked()
{

    try {
        QString date = ui->departureDate->text().trimmed();
        QString number = ui->trainNumber->text().trimmed();
        QString dest = ui->destination->text().trimmed();
        QString time = ui->departureTime->text().trimmed();
        QString seats = ui->availableSeats->text().trimmed();

        bool result = true;
        QString data;

        if (number.size() == 0) {
            data = "Номер поезда";
            result = false;
        }

        else if (dest.size() == 0) {
            data = "Пункт назначения";
            result = false;
        }

        else if (time.size() == 0) {
            data = "Время отправления";
            result = false;
        }

        else if (date.size() == 0) {
            data = "Дата выезда";
            result = false;
        }

        else if(seats.size() < 1 || seats.size() > 3) {
            data = "Количество свободных мест";
            result = false;
        }

       else if (!(time.size() == 5 &&
                   time[0].isDigit() && time[1].isDigit() &&
                   time[2] == ':' && time[3].isDigit() &&
                   time[4].isDigit())) {
            data = "Время отправления";
            result = false;
        }

        else if (!(stoi(time.toStdString().substr(0, 2)) >= 0 &&
                   stoi(time.toStdString().substr(0, 2)) <= 23 &&
                   stoi(time.toStdString().substr(3, 2)) >= 0 &&
                   stoi(time.toStdString().substr(3, 2)) <= 59)) {
                    data = "Время отправления";
                    result = false;
                }

        else if(date.size() != 10) {
            data = "Дата выезда";
            result = false;
        }

        else if (!date[0].isDigit() || !date[1].isDigit() || !date[3].isDigit() || !date[4].isDigit() || !date[6].isDigit() || !date[7].isDigit() || !date[8].isDigit() || !date[9].isDigit() || (date[2] != '.' || date[5] != '.')) {

            data = "Дата выезда";
            result = false;
        }

        else if ((date.mid(0, 2)).toInt() <= 0 || (date.mid(0, 2)).toInt() >= 32 || date.mid(3, 2).toInt() <= 0 || date.mid(3, 2).toInt() >= 13 || date.mid(6, 4).toInt() <= 0 || date.mid(6, 4).toInt() >= 10000) {
            data = "Дата выезда";
            result = false;
        }

        else if ((date.mid(0, 2)).toInt() > 30 && ((date.mid(3, 2)).toInt() == 4 || date.mid(3, 2).toInt() == 6 || date.mid(3, 2).toInt() == 9 || date.mid(3, 2).toInt() == 11)) {
            data = "Дата выезда";
            result = false;
        }

        else if ((date.mid(0, 2)).toInt() > 31 && ((date.mid(3, 2)).toInt() == 1 || date.mid(3, 2).toInt() == 3 || date.mid(3, 2).toInt() == 5 || date.mid(3, 2).toInt() == 7 || date.mid(3, 2).toInt() == 8 || date.mid(3, 2).toInt() == 10 || date.mid(3, 2).toInt() == 12)) {
            data = "Дата выезда";
            result = false;
        }

        else if (date.mid(0, 2).toInt() > 29 && date.mid(3, 2).toInt() == 2) {
            data = "Дата выезда";
            result = false;
        }

        else if (date.mid(0, 2).toInt() > 28 && date.mid(3, 2).toInt() == 2 && date.mid(6, 4).toInt() % 4 != 0) {
            data = "Дата выезда";
            result = false;
        }

        else if(result) { for(int j = 0; j < seats.size(); j++) {
            if(!seats[j].isDigit()) {
                data = "Количество свободных мест";
                result = false;
                break;
            }
        }
        }

        if(!res && result) {
            trainsList[indexx].setInfoAboutDeparture(seats.toInt(), number, date, time, dest);
            res = true;
            QMessageBox::information(this, "Success!", "Выбранный вами рейс был успешно изменен!");
            QFile file(fileName);
            file.open(QIODevice::WriteOnly | QIODevice::Truncate);

            for (int i = 0; i < trainsList.getSize(); i++) {

            QByteArray str;
            str = QByteArray::fromStdString(trainsList[i].getDepartureDate().toStdString());

            file.write(str + "\n");
            str = QByteArray::fromStdString(trainsList[i].getTrainNumber().toStdString());

            file.write(str + "\n");

            str = QByteArray::fromStdString(trainsList[i].getDestination().toStdString());
            file.write(str + "\n");

            str = QByteArray::fromStdString(trainsList[i].getDepartureTime().toStdString());
            file.write(str + "\n");

            str = QByteArray::fromStdString(QString::number(trainsList[i].getAvailableSeats()).toStdString());
            file.write(str + "\n");

           }
            this->close();
            emit firstWindow();
        }

        else if (result && res) {

            TrainTimetable newTrain;

            int seat = seats.toInt();

            newTrain.setInfoAboutDeparture(seat, number, date, time, dest);
            trainsList.push_back(newTrain);

            QFile file(fileName);
            file.open(QIODevice::ReadWrite);

            QString date1, time1, destination1, number1, seats1;
            TrainTimetable firstTrain;

            while(!file.atEnd()) {
                date1 = file.readLine().trimmed();
                number1 = file.readLine().trimmed();
                destination1 = file.readLine().trimmed();
                time1 = file.readLine().trimmed();
                seats1 = file.readLine().trimmed();
                firstTrain.setInfoAboutDeparture(seats1.toInt(), number1, date1, time1, destination1);
                trainsList.push_back(firstTrain);
                counter++;
            }
            counter++;

            QByteArray str;
            str = QByteArray::fromStdString(date.toStdString());


            file.write(str + "\n");
            str = QByteArray::fromStdString(number.toStdString());

            file.write(str + "\n");

            str = QByteArray::fromStdString(dest.toStdString());
            file.write(str + "\n");

            str = QByteArray::fromStdString(time.toStdString());
            file.write(str + "\n");

            str = QByteArray::fromStdString(seats.toStdString());
            file.write(str + "\n");

            ui->departureDate->clear();
            ui->trainNumber->clear();
            ui->destination->clear();
            ui->departureTime->clear();
            ui->availableSeats->clear();

            QMessageBox::information(this, "SUCCESS!", "Данные о рейсе успешно сохранены!\nДоступен ввод данных для нового рейса!");
        }

        else QMessageBox::critical(this, "ERROR!", "Данные в графе '" + data + "' введены неверно!\nПовторите ввод данных!");
 }
    catch(...) {
        QMessageBox::information(this, "ERROR!", "Данные о рейсе не сохранены!\nПовторите попытку!");
    }
}

void MainWindow::on_showList_clicked()
{
    QWidget *showwindow = new QWidget();
        showwindow->setWindowTitle("Расписание рейсов");
        showwindow->setGeometry(QRect(450, 150, 800, 250));
        showwindow->resize(650, 500);

        QTableWidget *tableWidget = new QTableWidget();
        QGridLayout *layout = new QGridLayout(showwindow);
        layout->addWidget(tableWidget, 0, 0);

        tableWidget->setColumnCount(5);
        tableWidget->setShowGrid(true);

        QStringList headers1;
                headers1.append("Дата вызеда");
                headers1.append("Время выезда");
                headers1.append("Номер поезда");
                headers1.append("Путь назначения");
                headers1.append("Количество свободных мест");
        tableWidget->setHorizontalHeaderLabels(headers1);

        tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);

        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

        int newcount = 0, count = 0;
        for (int i = 0; i < trainsList.getSize(); i++) {
            tableWidget->insertRow(i);
            tableWidget->setItem(i, 0, new QTableWidgetItem(trainsList[i].getDepartureDate()));
            tableWidget->setItem(i, 1, new QTableWidgetItem(trainsList[i].getDepartureTime()));
            tableWidget->setItem(i, 2, new QTableWidgetItem(trainsList[i].getTrainNumber()));
            tableWidget->setItem(i, 3, new QTableWidgetItem(trainsList[i].getDestination()));
            if(trainsList[i].getAvailableSeats() == 0) {
                                QTableWidgetItem* newItem = new QTableWidgetItem(QString::number(trainsList[i].getAvailableSeats()));
                                newItem->setBackground(Qt::red);
                                tableWidget->setItem(i, 4, newItem);
                                newcount++;
            }
            else tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(trainsList[i].getAvailableSeats())));
            tableWidget->resizeColumnsToContents();
            count++;
        }
        if (count == 0 && trainsList.getSize() == 0) {
            QMessageBox::critical(this, "ERROR!", "Список рейсов пуст!\nЗаполните список и повторите ввод параметров поиска!");
        }
        else {
        if(newcount != 0) {
            QMessageBox::critical(this, "WARNING!", "Обратите внимание, при наличии красной ячейки на рейсе,\nневозможно выполнить заказ в полном объеме!");
        }
        showwindow->show();
        }
}

void MainWindow::on_chooseFile_clicked()
{
    QString nameFile;

    nameFile = QFileDialog::getOpenFileName(this, "Открытие документа", "C:\\", "Текстовые файлы (*.txt);");

    QFile file(nameFile);
    QString str;
    int result = 0;

    try {
        file.open(QIODevice::ReadOnly);

        if(file.size() == 0) result++;

        if(result > 0) {
             QMessageBox::critical(this, "Внимание!", "Выбранный вами файл не может быть использован\nв качестве источника ресурсов, так как он \nсодержит неподходящие данные");

        }

        while(!file.atEnd()) {
    result = 0;

    str = file.readLine().trimmed();
    if(str.size() == 0) {
        result++;
    }

    if(result == 0 && (str.size() > 10 || str.size() < 10)) {
        result++;
    }

    if(result == 0 && (!str[0].isDigit() || !str[1].isDigit() ||
     str[2] != '.' || !str[3].isDigit() ||
     !str[4].isDigit() || str[5] != '.' ||
     !str[6].isDigit() || !str[7].isDigit() ||
     !str[8].isDigit() || !str[9].isDigit())) {
        result++;
    }

    if(result == 0) {
        QDate datee(str.mid(6, 4).toInt(), str.mid(3, 2).toInt(), str.mid(0, 2).toInt());
        if (!datee.isValid()) result++;
    }

    str = file.readLine().trimmed();
    str = file.readLine().trimmed();
    str = file.readLine().trimmed();

    if(str.size() == 0) {
         result++;
    }

    if(str.size() > 5 || str.size() < 5) {
        result++;
    }

    if(result == 0 && (!str[0].isDigit() || !str[1].isDigit() ||
       str[2] != ':' || !str[3].isDigit() ||
       !str[4].isDigit())) {
        result++;
    }

    if(result == 0) {
        QTime timee(str.mid(0, 2).toInt(), str.mid(3, 2).toInt(), 0, 0);
        if (!timee.isValid()) result++;
    }

    str = file.readLine().trimmed();

    if(str.size() == 0) {
         result++;
    }

    if(str.size() > 3) {
        result++;
    }

    if (result == 0) {
        for (int j = 0; j < str.size(); j++) {
            if(!str[j].isDigit()) result++;
        }
    }

    if(result == 0){
      fileName = nameFile;
       ui->filePath->setText(fileName);
    }

    if(result > 0) {

         QMessageBox::critical(this, "Внимание!", "Выбранный вами файл не может быть использован\nв качестве источника ресурсов, так как он \nсодержит неподходящие данные");
         break;
    }

    }
    }

    catch (...) {
         QMessageBox::critical(this, "Внимание!", "Не удалось открыть выбранный вами файл!");
    }
}


void MainWindow::on_showSpecialList_clicked()
{
    pwindow->show();
    this->close();
}

bool choose = true;

void specialSearch::on_saveData_clicked()
{
    QString inputDestination, inputTime;
    inputDestination = ui->todestination->text().trimmed();
    inputTime = ui->time->text().trimmed();

    bool trueValue = true;

    if(inputTime.size() == 0 || inputDestination.size() == 0) {
        trueValue = false;
    }

    else if(inputTime.size() > 5 || inputTime.size() < 5) {
        trueValue = false;
    }

    else if(!inputTime[0].isDigit() || !inputTime[1].isDigit() ||
       inputTime[2] != ':' || !inputTime[3].isDigit() ||
       !inputTime[4].isDigit()) {
        trueValue = false;
    }

    else if(trueValue) {
        QTime timee(inputTime.mid(0, 2).toInt(), inputTime.mid(3, 2).toInt(), 0, 0);
        if (!timee.isValid()) trueValue = false;
    }

    if (!trueValue) {
        QMessageBox::critical(this, "ERROR!", "Данные введены неверно!\nПовторите ввод данных!");
    }
    else {
    this->close();
    emit firstWindow();

        QWidget *showwindow = new QWidget();
            showwindow->setWindowTitle("Расписание рейсов по указанным параметрам");
            showwindow->setGeometry(QRect(450, 150, 800, 250));
            showwindow->resize(650, 500);

            QTableWidget *tableWidget = new QTableWidget();
            QGridLayout *layout = new QGridLayout(showwindow);
            layout->addWidget(tableWidget, 0, 0);

            tableWidget->setColumnCount(5);
            tableWidget->setShowGrid(true);

            QStringList headers1;
                    headers1.append("Дата вызеда");
                    headers1.append("Время выезда");
                    headers1.append("Номер поезда");
                    headers1.append("Путь назначения");
                    headers1.append("Количество свободных мест");
            tableWidget->setHorizontalHeaderLabels(headers1);

            tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);

            tableWidget->horizontalHeader()->setStretchLastSection(true);
            tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

            int count = 0, newcount = 0;
            int j = 0;
            for (int i = 0; i < trainsList.getSize(); i++) {
                QTime newtime(inputTime.mid(0, 2).toInt(), inputTime.mid(3, 2).toInt(), 0, 0);
                QTime newtime2(trainsList[i].getDepartureTime().mid(0, 2).toInt(), trainsList[i].getDepartureTime().mid(3, 2).toInt(), 0, 0);
                if (inputDestination == trainsList[i].getDestination() &&
                    newtime2 <= newtime) {
                tableWidget->insertRow(j);
                tableWidget->setItem(j, 0, new QTableWidgetItem(trainsList[i].getDepartureDate()));
                tableWidget->setItem(j, 1, new QTableWidgetItem(trainsList[i].getDepartureTime()));
                tableWidget->setItem(j, 2, new QTableWidgetItem(trainsList[i].getTrainNumber()));
                tableWidget->setItem(j, 3, new QTableWidgetItem(trainsList[i].getDestination()));
                if(trainsList[i].getAvailableSeats() == 0) {
                    QTableWidgetItem* newItem = new QTableWidgetItem(QString::number(trainsList[i].getAvailableSeats()));
                    newItem->setBackground(Qt::red);
                    tableWidget->setItem(j, 4, newItem);
                    newcount++;
                }
                else tableWidget->setItem(j, 4, new QTableWidgetItem(QString::number(trainsList[i].getAvailableSeats())));
                tableWidget->resizeColumnsToContents();
                count++;
                j++;
                }
            }
            if(newcount != 0) {
                QMessageBox::critical(this, "WARNING!", "Обратите внимание, при наличии красной ячейки на рейсе,\nневозможно выполнить заказ в полном объеме!");
            }
            if (count == 0 && trainsList.getSize() == 0) {
                ui->todestination->clear();
                ui->time->clear();
                QMessageBox::critical(this, "ERROR!", "Список рейсов пуст!\nЗаполните список и повторите ввод параметров поиска!");
            }
            else if(count == 0) {
                ui->todestination->clear();
                ui->time->clear();
                QMessageBox::critical(this, "ERROR!", "К сожалению, нет рейсов по заданным параметрам!:(");
            }
            else {
                ui->todestination->clear();
                ui->time->clear();
                showwindow->show();
            }
}
    }


void MainWindow::on_deleteNode_clicked()
{
    if(trainsList.getSize() == 0) {
        QMessageBox::critical(this, "ERROR!", "Список рейсов пуст!\nЗаполните список и повторите действие!");
    }
    else {
        choose = true;
        ui->listWidget->clear();
        ui->exit->show();
        ui->listWidget->show();
        ui->delete_reis->show();
        ui->chooseFile->hide();
        ui->editNode->hide();
        ui->showList->hide();
        ui->addNode->hide();
        ui->searchNode->hide();
        ui->picture->hide();
        ui->deleteNode->hide();
        ui->mergesort->hide();
        ui->showSpecialList->hide();
        this->setWindowTitle("Удаление рейса");

        for (int i = 0; i < trainsList.getSize(); i++) {
          ui->listWidget->addItem(trainsList[i].getTrainNumber());
        }
    }
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    try {
    if(choose) {
    QMessageBox::information(this, "Success!", "Выбранный вами рейс был успешно удален из списка!");

    for (int i = 0; i < trainsList.getSize(); i++) {
      if(trainsList[i].getTrainNumber() == ui->listWidget->currentItem()->text()) {
          trainsList.removeAt(i);
          QFile file(fileName);
          file.open(QIODevice::WriteOnly | QIODevice::Truncate);

          for (int i = 0; i < trainsList.getSize(); i++) {

          QByteArray str;
          str = QByteArray::fromStdString(trainsList[i].getDepartureDate().toStdString());

          file.write(str + "\n");
          str = QByteArray::fromStdString(trainsList[i].getTrainNumber().toStdString());

          file.write(str + "\n");

          str = QByteArray::fromStdString(trainsList[i].getDestination().toStdString());
          file.write(str + "\n");

          str = QByteArray::fromStdString(trainsList[i].getDepartureTime().toStdString());
          file.write(str + "\n");

          str = QByteArray::fromStdString(QString::number(trainsList[i].getAvailableSeats()).toStdString());
          file.write(str + "\n");

         }

          break;
        }
    }

    ui->listWidget->clear();
    for (int i = 0; i < trainsList.getSize(); i++) {
      ui->listWidget->addItem(trainsList[i].getTrainNumber());
    }
    }
    else if(!choose) {


        for (int i = 0; i < trainsList.getSize(); i++) {
          if(trainsList[i].getTrainNumber() == ui->listWidget->currentItem()->text()) {
              res = false;
              indexx = i;
              window->show();
              this->close();


              break;
            }
        }

        ui->listWidget->clear();
        ui->listWidget->hide();
        ui->delete_reis->hide();
        ui->chooseFile->show();
        ui->editNode->show();
        ui->showList->show();
        ui->addNode->show();
        ui->searchNode->show();
        ui->picture->show();
        ui->deleteNode->show();
        ui->mergesort->show();
        ui->showSpecialList->show();
        ui->exit->hide();
        ui->edit_reis->hide();
        this->setWindowTitle("Главная");
    }
    }
    catch (...) {
         QMessageBox::critical(this, "Внимание!", "Не удалось открыть выбранный вами файл!");
    }
}

void MainWindow::on_exit_clicked()
{
        ui->listWidget->hide();
        ui->delete_reis->hide();
        ui->chooseFile->show();
        ui->editNode->show();
        ui->showList->show();
        ui->addNode->show();
        ui->searchNode->show();
        ui->picture->show();
        ui->deleteNode->show();
        ui->mergesort->show();
        ui->showSpecialList->show();
        ui->exit->hide();
        ui->edit_reis->hide();
        this->setWindowTitle("Главная");
}

void MainWindow::on_editNode_clicked()
{
    choose = false;
    if(trainsList.getSize() == 0) {
        QMessageBox::critical(this, "ERROR!", "Список рейсов пуст!\nЗаполните список и повторите действие!");
    }
    else {
        choose = false;
        ui->listWidget->clear();
        ui->exit->show();
        ui->listWidget->show();
        ui->edit_reis->show();
        ui->chooseFile->hide();
        ui->editNode->hide();
        ui->showList->hide();
        ui->addNode->hide();
        ui->searchNode->hide();
        ui->picture->hide();
        ui->deleteNode->hide();
        ui->mergesort->hide();
        ui->showSpecialList->hide();
        this->setWindowTitle("Изменение рейса");

        for (int i = 0; i < trainsList.getSize(); i++) {
          ui->listWidget->addItem(trainsList[i].getTrainNumber());
        }
    }
}


void MainWindow::on_searchNode_clicked()
{
    if (trainsList.getSize() == 0) {
        QMessageBox::critical(this, "ERROR!", "Список рейсов пуст!\nЗаполните список и повторите ввод параметров поиска!");
    }
    else {
        pDialog->show();
        this->close();
    }
}

void Dialog::on_pushButton_save_clicked()
{
    QString inputNumber, inputDate;
    inputNumber = ui->inputNumberForSearch->text().trimmed();
    inputDate = ui->inputDateForSearch->text().trimmed();

    bool trueValue = true;

    if(inputNumber.size() == 0 || inputDate.size() == 0) {
        trueValue = false;
    }

    else if(inputDate.size() > 10 || inputDate.size() < 10) {
        trueValue = false;
    }

    else if(!inputDate[0].isDigit() || !inputDate[1].isDigit() ||
     inputDate[2] != '.' || !inputDate[3].isDigit() ||
     !inputDate[4].isDigit() || inputDate[5] != '.' ||
     !inputDate[6].isDigit() || !inputDate[7].isDigit() ||
     !inputDate[8].isDigit() || !inputDate[9].isDigit()) {
        trueValue = false;
    }

    if(trueValue) {
        QDate datee(inputDate.mid(6, 4).toInt(), inputDate.mid(3, 2).toInt(), inputDate.mid(0, 2).toInt());
        if (!datee.isValid()) trueValue = false;
    }

    if (!trueValue) {
        QMessageBox::critical(this, "ERROR!", "Данные введены неверно!\nПовторите ввод данных!");
    }
    else {
    this->close();
    emit firstWindow();

        QWidget *showwindow = new QWidget();
            showwindow->setWindowTitle("Расписание рейсов по указанным параметрам");
            showwindow->setGeometry(QRect(450, 150, 800, 250));
            showwindow->resize(650, 500);

            QTableWidget *tableWidget = new QTableWidget();
            QGridLayout *layout = new QGridLayout(showwindow);
            layout->addWidget(tableWidget, 0, 0);

            tableWidget->setColumnCount(5);
            tableWidget->setShowGrid(true);

            QStringList headers1;
                    headers1.append("Дата вызеда");
                    headers1.append("Время выезда");
                    headers1.append("Номер поезда");
                    headers1.append("Путь назначения");
                    headers1.append("Количество свободных мест");
            tableWidget->setHorizontalHeaderLabels(headers1);

            tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);

            tableWidget->horizontalHeader()->setStretchLastSection(true);
            tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

            int count = 0, newcount = 0;
            int j = 0;
            for (int i = 0; i < trainsList.getSize(); i++) {
                QDate dateNew(inputDate.mid(6, 4).toInt(), inputDate.mid(3, 2).toInt(), inputDate.mid(0, 2).toInt());
                QDate dateNew1(trainsList[i].getDepartureDate().mid(6, 4).toInt(), trainsList[i].getDepartureDate().mid(3, 2).toInt(), trainsList[i].getDepartureDate().mid(0, 2).toInt());
                if (inputNumber == trainsList[i].getTrainNumber() &&
                    dateNew == dateNew1) {
                tableWidget->insertRow(j);
                tableWidget->setItem(j, 0, new QTableWidgetItem(trainsList[i].getDepartureDate()));
                tableWidget->setItem(j, 1, new QTableWidgetItem(trainsList[i].getDepartureTime()));
                tableWidget->setItem(j, 2, new QTableWidgetItem(trainsList[i].getTrainNumber()));
                tableWidget->setItem(j, 3, new QTableWidgetItem(trainsList[i].getDestination()));
                if(trainsList[i].getAvailableSeats() == 0) {
                    QTableWidgetItem* newItem = new QTableWidgetItem(QString::number(trainsList[i].getAvailableSeats()));
                    newItem->setBackground(Qt::red);
                    tableWidget->setItem(j, 4, newItem);
                    newcount++;
                }
                else tableWidget->setItem(j, 4, new QTableWidgetItem(QString::number(trainsList[i].getAvailableSeats())));
                tableWidget->resizeColumnsToContents();
                count++;
                j++;
                }
            }
            if(newcount != 0) {
                QMessageBox::critical(this, "WARNING!", "Обратите внимание, при наличии красной ячейки на рейсе,\nневозможно выполнить заказ в полном объеме!");
            }
            else if(count == 0) {
                ui->inputDateForSearch->clear();
                ui->inputNumberForSearch->clear();
                QMessageBox::critical(this, "ERROR!", "К сожалению, нет рейсов по заданным параметрам!:(");
            }
            else {
                ui->inputDateForSearch->clear();
                ui->inputNumberForSearch->clear();
                showwindow->show();
            }
}
}

bool compareDate(const TrainTimetable& train1, const TrainTimetable& train2) {
    QDate str1(train1.getDepartureDate().mid(6, 4).toInt(), train1.getDepartureDate().mid(3, 2).toInt(), train1.getDepartureDate().mid(0, 2).toInt());
    QDate str2(train2.getDepartureDate().mid(6, 4).toInt(), train2.getDepartureDate().mid(3, 2).toInt(), train2.getDepartureDate().mid(0, 2).toInt());
        if (str1 < str2) return true;
        if (str1 > str2) return false;
    return false;
}

bool compareTime(const TrainTimetable& train1, const TrainTimetable& train2) {
    QTime str1(train1.getDepartureTime().mid(0, 2).toInt(), train1.getDepartureTime().mid(3, 2).toInt(), 0, 0);
    QTime str2(train2.getDepartureTime().mid(0, 2).toInt(), train2.getDepartureTime().mid(3, 2).toInt(), 0, 0);
        if (str1 < str2) return true;
        if (str1 > str2) return false;
    return false;
}

bool compareDestination(const TrainTimetable& train1, const TrainTimetable& train2) {
    QString str1 = train1.getDestination();
        QString str2 = train2.getDestination();
        for (int i = 0; i < train1.getDestination().length() && i < train2.getDestination().length(); ++i) {
            if (str1[i].toLower() < str2[i].toLower()) return true;
            if (str1[i].toLower() > str2[i].toLower()) return false;
        }
    return false;
}

bool compareSeats(const TrainTimetable& train1, const TrainTimetable& train2) {
    int seats1 = train1.getAvailableSeats();
    int seats2 = train2.getAvailableSeats();
        if (seats1 < seats2) return true;
        if (seats1 > seats2) return false;
    return false;
}

void sort() {
    auto arr = new TrainTimetable[trainsList.getSize()];
        for (int i = 0; i < trainsList.getSize(); ++i) {
            arr[i] = trainsList[i];
        }
        if (criteriaOfSort == 1) {
        merge_sort(arr, trainsList.getSize(), compareDate);
        }
        else if (criteriaOfSort == 2) {
        merge_sort(arr, trainsList.getSize(), compareTime);
        }
        else if (criteriaOfSort == 3) {
        merge_sort(arr, trainsList.getSize(), compareDestination);
        }
        else if (criteriaOfSort == 4) {
        merge_sort(arr, trainsList.getSize(), compareSeats);
        }
        QWidget *showwindow = new QWidget();
            showwindow->setWindowTitle("Отсортированное расписание рейсов");
            showwindow->setGeometry(QRect(450, 150, 800, 250));
            showwindow->resize(650, 500);

            QTableWidget *tableWidget = new QTableWidget();
            QGridLayout *layout = new QGridLayout(showwindow);
            layout->addWidget(tableWidget, 0, 0);

            tableWidget->setColumnCount(5);
            tableWidget->setShowGrid(true);

            QStringList headers1;
                    headers1.append("Дата вызеда");
                    headers1.append("Время выезда");
                    headers1.append("Номер поезда");
                    headers1.append("Путь назначения");
                    headers1.append("Количество свободных мест");
            tableWidget->setHorizontalHeaderLabels(headers1);

            tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);

            tableWidget->horizontalHeader()->setStretchLastSection(true);
            tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

            int newcount = 0;
            int j = 0;
            for (int i = 0; i < trainsList.getSize(); ++i) {
                trainsList[i] = arr[i];
                tableWidget->insertRow(j);
                tableWidget->setItem(j, 0, new QTableWidgetItem(trainsList[i].getDepartureDate()));
                tableWidget->setItem(j, 1, new QTableWidgetItem(trainsList[i].getDepartureTime()));
                tableWidget->setItem(j, 2, new QTableWidgetItem(trainsList[i].getTrainNumber()));
                tableWidget->setItem(j, 3, new QTableWidgetItem(trainsList[i].getDestination()));
                if(trainsList[i].getAvailableSeats() == 0) {
                    QTableWidgetItem* newItem = new QTableWidgetItem(QString::number(trainsList[i].getAvailableSeats()));
                    newItem->setBackground(Qt::red);
                    tableWidget->setItem(j, 4, newItem);
                    newcount++;
                }
                else tableWidget->setItem(j, 4, new QTableWidgetItem(QString::number(trainsList[i].getAvailableSeats())));
                tableWidget->resizeColumnsToContents();


            }
                showwindow->show();

        delete[] arr;
}

void MainWindow::on_mergesort_clicked()
{
    if (trainsList.getSize() == 0) {
        QMessageBox::critical(this, "ERROR!", "Список рейсов пуст!\nЗаполните список и повторите действие!");
    }
    else {
       critSort->show();
    }
}

void variantsOfSort::on_dateSort_clicked()
{
    criteriaOfSort = 1;
    this->close();
    QMessageBox::information(this, "Success!", "Сортировка списка по дате выезда была успешно выполнена!");
    QMessageBox::critical(this, "WARNING!", "Обратите внимание, при наличии красной ячейки на рейсе,\nневозможно выполнить заказ в полном объеме!");
    sort();
}


void variantsOfSort::on_TimeSort_clicked()
{
    criteriaOfSort = 2;
    this->close();
    QMessageBox::information(this, "Success!", "Сортировка списка по времени выезда была успешно выполнена!");
    QMessageBox::critical(this, "WARNING!", "Обратите внимание, при наличии красной ячейки на рейсе,\nневозможно выполнить заказ в полном объеме!");
    sort();
}


void variantsOfSort::on_destinationSort_clicked()
{
    criteriaOfSort = 3;
    this->close();
    QMessageBox::information(this, "Success!", "Сортировка списка по пункту назначения была успешно выполнена!");
    QMessageBox::critical(this, "WARNING!", "Обратите внимание, при наличии красной ячейки на рейсе,\nневозможно выполнить заказ в полном объеме!");
    sort();
}


void variantsOfSort::on_seatsSort_clicked()
{
    criteriaOfSort = 4;
    this->close();
    QMessageBox::information(this, "Success!", "Сортировка списка по количеству свободных мест была успешно выполнена!");
    QMessageBox::critical(this, "WARNING!", "Обратите внимание, при наличии красной ячейки на рейсе,\nневозможно выполнить заказ в полном объеме!");
    sort();
}
