#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include "employee.h"
#include "ArrayList.cpp"
#include <QTableWidget>
#include <QHeaderView>
#include <QFileDialog>
#include "mergeSort.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_exit->hide();
    ui->listWidget->hide();
    ui->label_info->hide();
    ui->label_info1->hide();
    this->setWindowTitle("Главная");
    newEmployee = new addNewEmployee();
    nameSearch = new searchname();
    editWindow = new editEmployee();
    inputSalary = new inputSearchSalary();
    inputHours = new hoursParametr();
    sortChoose = new inputOverHours();
    connect(sortChoose, &inputOverHours::firstWindow, this, &MainWindow::show);
    connect(inputHours, &hoursParametr::firstWindow, this, &MainWindow::show);
    connect(editWindow, &editEmployee::firstWindow, this, &MainWindow::show);
    connect(inputSalary, &inputSearchSalary::firstWindow, this, &MainWindow::show);
    connect(nameSearch, &searchname::firstWindow, this, &MainWindow::show);
    connect(newEmployee, &addNewEmployee::firstWindow, this, &MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString fileName = "C:\\FilesForQtLabs\\employees.txt";
List<Employee> employees;
bool res = true;
int indexx = 0;

void MainWindow::on_pushButton_addEmployee_clicked()
{
    newEmployee->show();
    this->close();
}

void addNewEmployee::on_pushButton_saveData_clicked()
{
    try {
        QString name = ui->lineEdit_name->text().trimmed();
        QString surname = ui->lineEdit_surname->text().trimmed();
        QString patronymicName = ui->lineEdit_patrionymicName->text().trimmed();
        QString tabelNumber = ui->lineEdit_tabelNumber->text().trimmed();
        QString hoursWorked = ui->lineEdit_hoursWorked->text().trimmed();
        QString rate = ui->lineEdit_rate->text().trimmed();

        bool result = true;
        QString data;

        if (name.size() == 0) {
            data = "Имя";
            result = false;
        }

        else if (surname.size() == 0) {
            data = "Фамилия";
            result = false;
        }

        else if (patronymicName.size() == 0) {
            data = "Отчество";
            result = false;
        }

        else if (tabelNumber.size() == 0) {
            data = "Табельный номер";
            result = false;
        }

        else if (hoursWorked.size() == 0) {
            data = "Количество проработанных за месяц часов";
            result = false;
        }

        else if (rate.size() == 0) {
            data = "Почасовой тариф";
            result = false;
        }

        else if(hoursWorked.size() > 3) {
            data = "Количество проработанных за месяц часов";
            result = false;
        }

        if (hoursWorked.size() <= 3 && hoursWorked.size() > 0) {
            for(int i = 0; i < hoursWorked.size(); i++) {
                if(!hoursWorked[i].isDigit()) {
                    result = false;
                    break;
                }
            }
            if(result) {
                    if(hoursWorked.toInt() > 720) {
                        result = false;
                    }
            }
            data = "Количество проработанных за месяц часов";
        }

        if(result) {
            int nodigit = 0;
            for(int i = 0; i < rate.size(); i++) {
                if(!rate[i].isDigit()) {
                    if((rate[i] == '.') && nodigit == 0 && i != 0) {
                        nodigit++;
                    }
                    else {
                    result = false;
                    data = "Почасовой тариф";
                    break;
                    }
                }
            }
        }

        if(!res && result) {
            int hours = hoursWorked.toInt();
            double currentRate = rate.toDouble();

            employees[indexx].setName(name);
            employees[indexx].setSurname(surname);
            employees[indexx].setPatronymicName(patronymicName);
            employees[indexx].setTabelNumber(tabelNumber);
            employees[indexx].setHoursWorked(hours);
            employees[indexx].setRate(currentRate);
            res = true;
            QMessageBox::information(this, "Success!", "Данные выбранного вами сотрудника были успешно изменены!");
            QFile file(fileName);
            file.open(QIODevice::WriteOnly | QIODevice::Truncate);

            for (int i = 0; i < employees.getSize(); i++) {

                QByteArray str;
                str = QByteArray::fromStdString(employees[i].getName().toStdString());

                file.write(str + "\n");
                str = QByteArray::fromStdString(employees[i].getSurname().toStdString());

                file.write(str + "\n");

                str = QByteArray::fromStdString(employees[i].getPatronymicName().toStdString());
                file.write(str + "\n");

                str = QByteArray::fromStdString(employees[i].getTabelNumber().toStdString());
                file.write(str + "\n");

                str = QByteArray::fromStdString(QString::number(employees[i].getHoursWorked()).toStdString());
                file.write(str + "\n");

                str = QByteArray::fromStdString(QString::number(employees[i].getRate()).toStdString());
                file.write(str + "\n");

           }
            ui->lineEdit_name->clear();
            ui->lineEdit_surname->clear();
            ui->lineEdit_patrionymicName->clear();
            ui->lineEdit_tabelNumber->clear();
            ui->lineEdit_hoursWorked->clear();
            ui->lineEdit_rate->clear();
            this->close();
            emit firstWindow();
        }

        else if (result && res) {

            Employee newEmployee;

            int hours = hoursWorked.toInt();
            double currentRate = rate.toDouble();

            newEmployee.setName(name);
            newEmployee.setSurname(surname);
            newEmployee.setPatronymicName(patronymicName);
            newEmployee.setTabelNumber(tabelNumber);
            newEmployee.setHoursWorked(hours);
            newEmployee.setRate(currentRate);

            employees.push_back(newEmployee);

            QFile file(fileName);
            file.open(QIODevice::ReadWrite);

            Employee addEmployee;
            QString name1, surname1, patronymicName1, tabelNumber1;
            int hours1;
            double currentRate1;

            while(!file.atEnd()) {
                name1 = file.readLine().trimmed();
                surname1 = file.readLine().trimmed();
                patronymicName1 = file.readLine().trimmed();
                tabelNumber1 = file.readLine().trimmed();
                hours1 = file.readLine().trimmed().toInt();
                currentRate1 = file.readLine().trimmed().toDouble();
                addEmployee.setName(name1);
                addEmployee.setSurname(surname1);
                addEmployee.setPatronymicName(patronymicName1);
                addEmployee.setTabelNumber(tabelNumber1);
                addEmployee.setHoursWorked(hours1);
                addEmployee.setRate(currentRate1);
                employees.push_back(addEmployee);
            }

            QByteArray str;
            str = QByteArray::fromStdString(name.toStdString());

            file.write(str + "\n");
            str = QByteArray::fromStdString(surname.toStdString());

            file.write(str + "\n");

            str = QByteArray::fromStdString(patronymicName.toStdString());
            file.write(str + "\n");

            str = QByteArray::fromStdString(tabelNumber.toStdString());
            file.write(str + "\n");

            str = QByteArray::fromStdString(hoursWorked.toStdString());
            file.write(str + "\n");

            str = QByteArray::fromStdString(rate.toStdString());
            file.write(str + "\n");


            ui->lineEdit_name->clear();
            ui->lineEdit_surname->clear();
            ui->lineEdit_patrionymicName->clear();
            ui->lineEdit_tabelNumber->clear();
            ui->lineEdit_hoursWorked->clear();
            ui->lineEdit_rate->clear();

            QMessageBox::information(this, "SUCCESS!", "Данные о сотруднике успешно сохранены!\nДоступен ввод данных для нового сотрудника!");
        }

        else {
            if (data == "Почасовой тариф") {
            QMessageBox::critical(this, "ERROR!", "Данные в графе '" + data + "' введены неверно!\nПовторите ввод данных!\nОбратите внимание, что дробное число вводится со знаком '.'");
            }
            else {
            QMessageBox::critical(this, "ERROR!", "Данные в графе '" + data + "' введены неверно!\nПовторите ввод данных!");
            }
        }
 }
    catch(...) {
        QMessageBox::information(this, "ERROR!", "Данные о сотруднике не сохранены!\nПовторите попытку!");
    }
}


void MainWindow::on_pushButton_showList_clicked()
{
    if (employees.getSize() == 0) {
        QMessageBox::critical(this, "ERROR!", "Список сотрудников пуст!\nЗаполните список и повторите ввод даннных!");
    }
    else {
    QWidget *showwindow = new QWidget();
        showwindow->setWindowTitle("Список сотрудников");
        showwindow->setGeometry(QRect(450, 150, 850, 200));
        showwindow->resize(750, 500);

        QTableWidget *tableWidget = new QTableWidget();
        QGridLayout *layout = new QGridLayout(showwindow);
        layout->addWidget(tableWidget, 0, 0);

        tableWidget->setColumnCount(6);
        tableWidget->setShowGrid(true);

        QStringList headers1;
                headers1.append("Фамилия");
                headers1.append("Имя");
                headers1.append("Отчество");
                headers1.append("Табельный номер");
                headers1.append("Количество проработнных за месяц часов");
                headers1.append("Почасовой тариф");
        tableWidget->setHorizontalHeaderLabels(headers1);

        tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);

        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

        int newcount = 0, count = 0;
        for (int i = 0; i < employees.getSize(); i++) {
            tableWidget->insertRow(i);
            tableWidget->setItem(i, 0, new QTableWidgetItem(employees[i].getSurname()));
            tableWidget->setItem(i, 1, new QTableWidgetItem(employees[i].getName()));
            tableWidget->setItem(i, 2, new QTableWidgetItem(employees[i].getPatronymicName()));
            tableWidget->setItem(i, 3, new QTableWidgetItem(employees[i].getTabelNumber()));
            tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(employees[i].getHoursWorked())));
            tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(employees[i].getRate())));
            tableWidget->resizeColumnsToContents();
            count++;
        }
        showwindow->show();

    }
}


void MainWindow::on_pushButton_chooseFile_clicked()
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
            QMessageBox::critical(this, "ERROR", "Выбранный вами файл не может быть использован\nв качестве источника ресурсов, так как он \nсодержит неподходящие данные");

        }

        while(!file.atEnd()) {
    result = 0;

    str = file.readLine().trimmed();
    if(str.size() == 0) {
        result++;
    }

    str = file.readLine().trimmed();
    if(str.size() == 0) {
        result++;
    }

    str = file.readLine().trimmed();
    if(str.size() == 0) {
        result++;
    }

    str = file.readLine().trimmed();
    if(str.size() == 0) {
        result++;
    }

    str = file.readLine().trimmed();

    if(str.size() == 0) {
         result++;
    }

    if(str.size() > 3) {
        result++;
    }

    if (result == 0 && str.size() <= 3 && str.size() > 0) {
        for(int i = 0; i < str.size(); i++) {
            if(!str[i].isDigit()) {
                result++;
                break;
            }
        }
        if(result == 0) {
                if(str.toInt() > 720) {
                    result++;
                }
        }
    }

    str = file.readLine().trimmed();

    if(str.size() == 0) {
         result++;
    }

    int nodigit = 0;
    if(result == 0) {
        int nodigit = 0;
        for(int i = 0; i < str.size(); i++) {
            if(!str[i].isDigit()) {
                if((str[i] == '.') && nodigit == 0 && i != 0) {
                    nodigit++;
                }
                else {
                result++;
                break;
                }
            }
        }
    }

    if(result > 0) {

         QMessageBox::critical(this, "ERROR", "Выбранный вами файл не может быть использован\nв качестве источника ресурсов, так как он \nсодержит неподходящие данные");
         break;
    }

    }
        if (result == 0) {
            QMessageBox::information(this, "SUCCESS!", "Путь файла успешно сохранен!");
            fileName = nameFile;
            ui->pathFile->setText(fileName);
        }
    }

    catch (...) {
        QMessageBox::critical(this, "ERROR", "Не удалось открыть выбранный вами файл!");
    }
}

void MainWindow::on_pushButton_SearchFio_clicked()
{
    if(employees.getSize() == 0) {
        QMessageBox::critical(this, "ERROR!", "Список сотрудников пуст!\nЗаполните список и повторите действие!");
    }
    else {
    nameSearch->show();
    this->close();
    }
}

bool compareSurname(Employee& employee1, Employee& employee2) {
    QString str1 = employee1.getSurname();
    QString str2 = employee2.getSurname();
        for (int i = 0; i < employee1.getSurname().length() && i < employee2.getSurname().length(); ++i) {
            if (str1[i].toLower() < str2[i].toLower()) return true;
            if (str1[i].toLower() > str2[i].toLower()) return false;
        }
    return false;
}

bool compareName(Employee& employee1, Employee& employee2) {
    QString str1 = employee1.getName();
    QString str2 = employee2.getName();
        for (int i = 0; i < employee1.getName().length() && i < employee2.getName().length(); ++i) {
            if (str1[i].toLower() < str2[i].toLower()) return true;
            if (str1[i].toLower() > str2[i].toLower()) return false;
        }
    return false;
}

bool compareHours(Employee& employee1, Employee& employee2) {
    int hours1 = employee1.getHoursWorked();
    int hours2 = employee2.getHoursWorked();
        if (hours1 < hours2) return true;
        if (hours1 > hours2) return false;
    return false;
}

bool compareRate(Employee& employee1, Employee& employee2) {
    long double rate1 = employee1.getRate();
    long double rate2 = employee2.getRate();
        if (rate1 < rate2) return true;
        if (rate1 > rate2) return false;
    return false;
}

void searchname::on_pushButton_searchSurname_clicked()
{
     QString searchSurname = ui->lineEdit_nameSearch->text().trimmed();

    if (searchSurname.size() == 0) {
        QMessageBox::critical(this, "ERROR", "Фамилия сотрудника не может состоять из введенных данных!\nПовторите ввод фамилии!");
    }
    else {

        this->close();
        emit firstWindow();
        auto arr = new Employee[employees.getSize()];
            for (int i = 0; i < employees.getSize(); ++i) {
                arr[i] = employees[i];
            }
            merge_sort(arr, employees.getSize(), compareSurname);
        QWidget *showwindow = new QWidget();
            showwindow->setWindowTitle("Список заданных сотрудников");
            showwindow->setGeometry(QRect(450, 150, 850, 200));
            showwindow->resize(750, 500);

            QTableWidget *tableWidget = new QTableWidget();
            QGridLayout *layout = new QGridLayout(showwindow);
            layout->addWidget(tableWidget, 0, 0);

            tableWidget->setColumnCount(6);
            tableWidget->setShowGrid(true);

            QStringList headers1;
                    headers1.append("Фамилия");
                    headers1.append("Имя");
                    headers1.append("Отчество");
                    headers1.append("Табельный номер");
                    headers1.append("Количество проработнных за месяц часов");
                    headers1.append("Почасовой тариф");
            tableWidget->setHorizontalHeaderLabels(headers1);

            tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);

            tableWidget->horizontalHeader()->setStretchLastSection(true);
            tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

            ui->lineEdit_nameSearch->clear();

            int count = 0, ii = 0;
            for (int i = 0; i < employees.getSize(); i++) {
                employees[i] = arr[i];
                if(searchSurname == employees[i].getSurname()) {
                tableWidget->insertRow(ii);
                tableWidget->setItem(ii, 0, new QTableWidgetItem(employees[i].getSurname()));
                tableWidget->setItem(ii, 1, new QTableWidgetItem(employees[i].getName()));
                tableWidget->setItem(ii, 2, new QTableWidgetItem(employees[i].getPatronymicName()));
                tableWidget->setItem(ii, 3, new QTableWidgetItem(employees[i].getTabelNumber()));
                tableWidget->setItem(ii, 4, new QTableWidgetItem(QString::number(employees[i].getHoursWorked())));
                tableWidget->setItem(ii, 5, new QTableWidgetItem(QString::number(employees[i].getRate())));
                tableWidget->resizeColumnsToContents();
                count++;
                ii++;
                }
            }
            if(count == 0) {
                QMessageBox::critical(this, "ERROR", "Не найдено ни одного сотрудника с заданной фамилией!");
            }
            else showwindow->show();
            delete[] arr;
    }
}

bool choose = true;

void MainWindow::on_pushButton_deleteEmloyee_clicked()
{
    if(employees.getSize() == 0) {
        QMessageBox::critical(this, "ERROR!", "Список сотрудников пуст!\nЗаполните список и повторите действие!");
    }
    else {
        choose = true;
        ui->listWidget->clear();
        ui->pushButton_exit->show();
        ui->listWidget->show();
        ui->label_info->show();
        ui->pushButton_showList->hide();
        ui->pushButton_showSpecialList->hide();
        ui->pushButton_SortList->hide();
        ui->pushButton_editEmloyee->hide();
        ui->pushButton_deleteEmloyee->hide();
        ui->pushButton_chooseFile->hide();
        ui->pushButton_SearchFio->hide();
        ui->pushButton_addEmployee->hide();
        ui->label->hide();
        ui->picture->hide();
        ui->label_2->hide();
        ui->label_3->hide();
        this->setWindowTitle("Удаление сотрудника");

        for (int i = 0; i < employees.getSize(); i++) {
          ui->listWidget->addItem(employees[i].getSurname());
        }
    }
}


void MainWindow::on_pushButton_exit_clicked()
{
    ui->pushButton_exit->hide();
    ui->listWidget->hide();
    ui->label_info->hide();
    ui->pushButton_showList->show();
    ui->pushButton_showSpecialList->show();
    ui->pushButton_SortList->show();
    ui->pushButton_editEmloyee->show();
    ui->pushButton_deleteEmloyee->show();
    ui->pushButton_chooseFile->show();
    ui->pushButton_SearchFio->show();
    ui->pushButton_addEmployee->show();
    ui->label_info1->hide();
    ui->label_2->show();
    ui->label_3->show();
    ui->label->show();
    ui->picture->show();
    this->setWindowTitle("Главная");
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    try {
    if(choose) {
    QMessageBox::information(this, "Success!", "Выбранный вами сотрудник был успешно удален из списка!");

    for (int i = 0; i < employees.getSize(); i++) {
      if(employees[i].getSurname() == ui->listWidget->currentItem()->text()) {
          employees.removeAt(i);
          QFile file(fileName);
          file.open(QIODevice::WriteOnly | QIODevice::Truncate);

          for (int i = 0; i < employees.getSize(); i++) {

          QByteArray str;
          str = QByteArray::fromStdString(employees[i].getName().toStdString());

          file.write(str + "\n");
          str = QByteArray::fromStdString(employees[i].getSurname().toStdString());

          file.write(str + "\n");

          str = QByteArray::fromStdString(employees[i].getPatronymicName().toStdString());
          file.write(str + "\n");

          str = QByteArray::fromStdString(employees[i].getTabelNumber().toStdString());
          file.write(str + "\n");

          str = QByteArray::fromStdString(QString::number(employees[i].getHoursWorked()).toStdString());
          file.write(str + "\n");

          str = QByteArray::fromStdString(QString::number(employees[i].getRate()).toStdString());
          file.write(str + "\n");

         }

          break;
        }
    }

    ui->listWidget->clear();
    for (int i = 0; i < employees.getSize(); i++) {
      ui->listWidget->addItem(employees[i].getSurname());
    }
    }
    else if(!choose) {

        for (int i = 0; i < employees.getSize(); i++) {
          if(employees[i].getSurname() == ui->listWidget->currentItem()->text()) {
              res = false;
              indexx = i;
              newEmployee->show();
              this->close();


              break;
            }
        }

        ui->listWidget->clear();
        ui->pushButton_exit->hide();
        ui->listWidget->hide();
        ui->label_info1->hide();
        ui->pushButton_showList->show();
        ui->pushButton_showSpecialList->show();
        ui->pushButton_SortList->show();
        ui->pushButton_editEmloyee->show();
        ui->pushButton_deleteEmloyee->show();
        ui->pushButton_chooseFile->show();
        ui->pushButton_SearchFio->show();
        ui->pushButton_addEmployee->show();
        ui->label->show();
        ui->label_2->show();
        ui->label_3->show();
        ui->picture->show();
        this->setWindowTitle("Главная");
    }
    }
    catch (...) {
         QMessageBox::critical(this, "Внимание!", "Не удалось открыть выбранный вами файл!");
    }
}


void MainWindow::on_pushButton_editEmloyee_clicked()
{
    choose = false;
    if(employees.getSize() == 0) {
        QMessageBox::critical(this, "ERROR!", "Список сотрудников пуст!\nЗаполните список и повторите действие!");
    }
    else {
        choose = false;
        ui->listWidget->clear();
        ui->pushButton_exit->show();
        ui->listWidget->show();
        ui->label_info1->show();
        ui->pushButton_showList->hide();
        ui->pushButton_showSpecialList->hide();
        ui->pushButton_SortList->hide();
        ui->pushButton_editEmloyee->hide();
        ui->pushButton_deleteEmloyee->hide();
        ui->pushButton_chooseFile->hide();
        ui->pushButton_SearchFio->hide();
        ui->pushButton_addEmployee->hide();
        ui->label->hide();
        ui->picture->hide();
        ui->label_2->hide();
        ui->label_3->hide();
        this->setWindowTitle("Изменение данных о сотруднике");

        for (int i = 0; i < employees.getSize(); i++) {
          ui->listWidget->addItem(employees[i].getSurname());
        }
    }
}

void MainWindow::on_pushButton_showSpecialList_clicked()
{
    if(employees.getSize() == 0) {
        QMessageBox::critical(this, "ERROR!", "Список сотрудников пуст!\nЗаполните список и повторите действие!");
    }
    else {
    editWindow->show();
    this->close();
    }
}

void editEmployee::on_pushButton_listSalary_clicked()
{
    emit firstWindow();
    inputSalary->show();
    this->close();
}

void inputSearchSalary::on_pushButton_saveSalary_clicked()
{
    QString salary = ui->lineEdit_newSalary->text().trimmed();
    bool result = true;

    if(salary.size() == 0) {
        result = false;
    }

    if(result) {
        int nodigit = 0;
        for(int i = 0; i < salary.size(); i++) {
            if(!salary[i].isDigit()) {
                if((salary[i] == '.') && nodigit == 0 && i != 0) {
                    nodigit++;
                }
                else {
                result = false;
                break;
                }
            }
        }
    }
    if(result) {
        long double employeeSalary = salary.toDouble();

        this->close();

        QWidget *showwindow = new QWidget();
            showwindow->setWindowTitle("Список сотрудников с заданным параметром");
            showwindow->setGeometry(QRect(450, 150, 850, 200));
            showwindow->resize(750, 500);

            QTableWidget *tableWidget = new QTableWidget();
            QGridLayout *layout = new QGridLayout(showwindow);
            layout->addWidget(tableWidget, 0, 0);

            tableWidget->setColumnCount(6);
            tableWidget->setShowGrid(true);

            QStringList headers1;
                    headers1.append("Фамилия");
                    headers1.append("Имя");
                    headers1.append("Отчество");
                    headers1.append("Табельный номер");
                    headers1.append("Количество проработнных за месяц часов");
                    headers1.append("Почасовой тариф");
            tableWidget->setHorizontalHeaderLabels(headers1);

            tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);

            tableWidget->horizontalHeader()->setStretchLastSection(true);
            tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

            int count = 0, ii = 0;
            for (int i = 0; i < employees.getSize(); i++) {
                long double salary1;
                if(employees[i].getHoursWorked() > 144) {
                    salary1 = employees[i].getRate() * (employees[i].getHoursWorked() - 144) * 2 + 144 * employees[i].getRate();
                }
                if(employees[i].getHoursWorked() <= 144) {
                    salary1 = employees[i].getRate() * employees[i].getHoursWorked();
                }
                if(employeeSalary <= salary1) {
                tableWidget->insertRow(ii);
                tableWidget->setItem(ii, 0, new QTableWidgetItem(employees[i].getSurname()));
                tableWidget->setItem(ii, 1, new QTableWidgetItem(employees[i].getName()));
                tableWidget->setItem(ii, 2, new QTableWidgetItem(employees[i].getPatronymicName()));
                tableWidget->setItem(ii, 3, new QTableWidgetItem(employees[i].getTabelNumber()));
                tableWidget->setItem(ii, 4, new QTableWidgetItem(QString::number(employees[i].getHoursWorked())));
                tableWidget->setItem(ii, 5, new QTableWidgetItem(QString::number(employees[i].getRate())));
                tableWidget->resizeColumnsToContents();
                count++;
                ii++;
                }
            }
            if(count == 0) {
                QMessageBox::critical(this, "ERROR", "Не найдено ни одного сотрудника с заданной и выше зарплатой!");
            }
            else {
                showwindow->show();
            }
    }
    else if(!result) {
        QMessageBox::critical(this, "ERROR!", "Данные введены некорректно!\nПовторите ввод данных!");
    }
    ui->lineEdit_newSalary->clear();
}

void editEmployee::on_pushButton_listHours_clicked()
{
    emit firstWindow();
    inputHours->show();
    this->close();
}

void hoursParametr::on_pushButton_saveHours_clicked()
{
    QString workedHours = ui->lineEdit_hours->text().trimmed();
    bool result = true;

    if(workedHours.size() == 0) {
        result = false;
    }

    if(result) {
        for(int i = 0; i < workedHours.size(); i++) {
            if(!workedHours[i].isDigit()) {
                result = false;
                break;
            }
        }
    }
    if(result) {
        int employeeHours = workedHours.toInt();

        this->close();

        auto arr = new Employee[employees.getSize()];
            for (int i = 0; i < employees.getSize(); ++i) {
                arr[i] = employees[i];
            }
            merge_sort(arr, employees.getSize(), compareHours);

        QWidget *showwindow = new QWidget();
            showwindow->setWindowTitle("Список сотрудников с заданным параметром");
            showwindow->setGeometry(QRect(450, 150, 850, 200));
            showwindow->resize(750, 500);

            QTableWidget *tableWidget = new QTableWidget();
            QGridLayout *layout = new QGridLayout(showwindow);
            layout->addWidget(tableWidget, 0, 0);

            tableWidget->setColumnCount(6);
            tableWidget->setShowGrid(true);

            QStringList headers1;
                    headers1.append("Фамилия");
                    headers1.append("Имя");
                    headers1.append("Отчество");
                    headers1.append("Табельный номер");
                    headers1.append("Количество проработнных за месяц часов");
                    headers1.append("Почасовой тариф");
            tableWidget->setHorizontalHeaderLabels(headers1);

            tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);

            tableWidget->horizontalHeader()->setStretchLastSection(true);
            tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

            int count = 0, ii = 0;
            for (int i = 0; i < employees.getSize(); i++) {
                employees[i] = arr[i];
                if(employeeHours <= employees[i].getHoursWorked()) {
                tableWidget->insertRow(ii);
                tableWidget->setItem(ii, 0, new QTableWidgetItem(employees[i].getSurname()));
                tableWidget->setItem(ii, 1, new QTableWidgetItem(employees[i].getName()));
                tableWidget->setItem(ii, 2, new QTableWidgetItem(employees[i].getPatronymicName()));
                tableWidget->setItem(ii, 3, new QTableWidgetItem(employees[i].getTabelNumber()));
                tableWidget->setItem(ii, 4, new QTableWidgetItem(QString::number(employees[i].getHoursWorked())));
                tableWidget->setItem(ii, 5, new QTableWidgetItem(QString::number(employees[i].getRate())));
                tableWidget->resizeColumnsToContents();
                count++;
                ii++;
                }
            }
            if(count == 0) {
                QMessageBox::critical(this, "ERROR!", "Не найдено ни одного сотрудника с заданным количеством проработанных часов и выше!");
            }
            else {
                showwindow->show();
            }
            delete[] arr;
    }
    else if(!result) {
        QMessageBox::critical(this, "ERROR!", "Данные введены некорректно!\nПовторите ввод данных!");
    }
    ui->lineEdit_hours->clear();
}

void editEmployee::on_pushButton_listOverHours_clicked()
{
    emit firstWindow();
    this->close();

    auto arr = new Employee[employees.getSize()];
        for (int i = 0; i < employees.getSize(); ++i) {
            arr[i] = employees[i];
        }
        merge_sort(arr, employees.getSize(), compareHours);

    QWidget *showwindow = new QWidget();
        showwindow->setWindowTitle("Список сотрудников со сверхурочным количеством часов");
        showwindow->setGeometry(QRect(450, 150, 850, 200));
        showwindow->resize(750, 500);

        QTableWidget *tableWidget = new QTableWidget();
        QGridLayout *layout = new QGridLayout(showwindow);
        layout->addWidget(tableWidget, 0, 0);

        tableWidget->setColumnCount(6);
        tableWidget->setShowGrid(true);

        QStringList headers1;
                headers1.append("Фамилия");
                headers1.append("Имя");
                headers1.append("Отчество");
                headers1.append("Табельный номер");
                headers1.append("Количество проработнных за месяц часов");
                headers1.append("Почасовой тариф");
        tableWidget->setHorizontalHeaderLabels(headers1);

        tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);

        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

        int count = 0, ii = 0;
        for (int i = 0; i < employees.getSize(); i++) {
            employees[i] = arr[i];
            if(employees[i].getHoursWorked() > 144) {
            tableWidget->insertRow(ii);
            tableWidget->setItem(ii, 0, new QTableWidgetItem(employees[i].getSurname()));
            tableWidget->setItem(ii, 1, new QTableWidgetItem(employees[i].getName()));
            tableWidget->setItem(ii, 2, new QTableWidgetItem(employees[i].getPatronymicName()));
            tableWidget->setItem(ii, 3, new QTableWidgetItem(employees[i].getTabelNumber()));
            tableWidget->setItem(ii, 4, new QTableWidgetItem(QString::number(employees[i].getHoursWorked())));
            tableWidget->setItem(ii, 5, new QTableWidgetItem(QString::number(employees[i].getRate())));
            tableWidget->resizeColumnsToContents();
            count++;
            ii++;
            }
        }
        if(count == 0) {
            QMessageBox::critical(this, "ERROR!", "Не найдено ни одного сотрудника с заданным количеством проработанных часов и выше!");
        }
        else {
            showwindow->show();
        }
        delete[] arr;
}

void MainWindow::on_pushButton_SortList_clicked()
{
    if(employees.getSize() == 0) {
        QMessageBox::critical(this, "ERROR!", "Список сотрудников пуст!\nЗаполните список и повторите действие!");
    }
    else {
    sortChoose->show();
    this->close();
    }
}

void inputOverHours::on_pushButton_searchSurname_clicked()
{
    emit firstWindow();
    QWidget *showwindow = new QWidget();
    auto arr = new Employee[employees.getSize()];
        for (int i = 0; i < employees.getSize(); ++i) {
            arr[i] = employees[i];
        }
        merge_sort(arr, employees.getSize(), compareSurname);
        showwindow->setWindowTitle("Отсортированный список сотрудников");
        showwindow->setGeometry(QRect(450, 150, 850, 200));
        showwindow->resize(750, 500);

        QTableWidget *tableWidget = new QTableWidget();
        QGridLayout *layout = new QGridLayout(showwindow);
        layout->addWidget(tableWidget, 0, 0);

        tableWidget->setColumnCount(6);
        tableWidget->setShowGrid(true);

        QStringList headers1;
                headers1.append("Фамилия");
                headers1.append("Имя");
                headers1.append("Отчество");
                headers1.append("Табельный номер");
                headers1.append("Количество проработнных за месяц часов");
                headers1.append("Почасовой тариф");
        tableWidget->setHorizontalHeaderLabels(headers1);

        tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);

        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

        int count = 0, ii = 0;
        for (int i = 0; i < employees.getSize(); i++) {
            employees[i] = arr[i];
            tableWidget->insertRow(ii);
            tableWidget->setItem(ii, 0, new QTableWidgetItem(employees[i].getSurname()));
            tableWidget->setItem(ii, 1, new QTableWidgetItem(employees[i].getName()));
            tableWidget->setItem(ii, 2, new QTableWidgetItem(employees[i].getPatronymicName()));
            tableWidget->setItem(ii, 3, new QTableWidgetItem(employees[i].getTabelNumber()));
            tableWidget->setItem(ii, 4, new QTableWidgetItem(QString::number(employees[i].getHoursWorked())));
            tableWidget->setItem(ii, 5, new QTableWidgetItem(QString::number(employees[i].getRate())));
            tableWidget->resizeColumnsToContents();
            count++;
            ii++;
            }

            showwindow->show();
            this->close();
            delete[] arr;
}

void inputOverHours::on_pushButton_searchName_clicked()
{
    emit firstWindow();
    QWidget *showwindow = new QWidget();
    auto arr = new Employee[employees.getSize()];
        for (int i = 0; i < employees.getSize(); ++i) {
            arr[i] = employees[i];
        }
        merge_sort(arr, employees.getSize(), compareName);
        showwindow->setWindowTitle("Отсортированный список сотрудников");
        showwindow->setGeometry(QRect(450, 150, 850, 200));
        showwindow->resize(750, 500);

        QTableWidget *tableWidget = new QTableWidget();
        QGridLayout *layout = new QGridLayout(showwindow);
        layout->addWidget(tableWidget, 0, 0);

        tableWidget->setColumnCount(6);
        tableWidget->setShowGrid(true);

        QStringList headers1;
                headers1.append("Фамилия");
                headers1.append("Имя");
                headers1.append("Отчество");
                headers1.append("Табельный номер");
                headers1.append("Количество проработнных за месяц часов");
                headers1.append("Почасовой тариф");
        tableWidget->setHorizontalHeaderLabels(headers1);

        tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);

        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

        int count = 0, ii = 0;
        for (int i = 0; i < employees.getSize(); i++) {
            employees[i] = arr[i];
            tableWidget->insertRow(ii);
            tableWidget->setItem(ii, 0, new QTableWidgetItem(employees[i].getSurname()));
            tableWidget->setItem(ii, 1, new QTableWidgetItem(employees[i].getName()));
            tableWidget->setItem(ii, 2, new QTableWidgetItem(employees[i].getPatronymicName()));
            tableWidget->setItem(ii, 3, new QTableWidgetItem(employees[i].getTabelNumber()));
            tableWidget->setItem(ii, 4, new QTableWidgetItem(QString::number(employees[i].getHoursWorked())));
            tableWidget->setItem(ii, 5, new QTableWidgetItem(QString::number(employees[i].getRate())));
            tableWidget->resizeColumnsToContents();
            count++;
            ii++;
            }

            showwindow->show();
            this->close();
            delete[] arr;
}

void inputOverHours::on_pushButton_searchWorkedHours_clicked()
{
    emit firstWindow();
    QWidget *showwindow = new QWidget();
    auto arr = new Employee[employees.getSize()];
        for (int i = 0; i < employees.getSize(); ++i) {
            arr[i] = employees[i];
        }
        merge_sort(arr, employees.getSize(), compareHours);
        showwindow->setWindowTitle("Отсортированный список сотрудников");
        showwindow->setGeometry(QRect(450, 150, 850, 200));
        showwindow->resize(750, 500);

        QTableWidget *tableWidget = new QTableWidget();
        QGridLayout *layout = new QGridLayout(showwindow);
        layout->addWidget(tableWidget, 0, 0);

        tableWidget->setColumnCount(6);
        tableWidget->setShowGrid(true);

        QStringList headers1;
                headers1.append("Фамилия");
                headers1.append("Имя");
                headers1.append("Отчество");
                headers1.append("Табельный номер");
                headers1.append("Количество проработнных за месяц часов");
                headers1.append("Почасовой тариф");
        tableWidget->setHorizontalHeaderLabels(headers1);

        tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);

        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

        int count = 0, ii = 0;
        for (int i = 0; i < employees.getSize(); i++) {
            employees[i] = arr[i];
            tableWidget->insertRow(ii);
            tableWidget->setItem(ii, 0, new QTableWidgetItem(employees[i].getSurname()));
            tableWidget->setItem(ii, 1, new QTableWidgetItem(employees[i].getName()));
            tableWidget->setItem(ii, 2, new QTableWidgetItem(employees[i].getPatronymicName()));
            tableWidget->setItem(ii, 3, new QTableWidgetItem(employees[i].getTabelNumber()));
            tableWidget->setItem(ii, 4, new QTableWidgetItem(QString::number(employees[i].getHoursWorked())));
            tableWidget->setItem(ii, 5, new QTableWidgetItem(QString::number(employees[i].getRate())));
            tableWidget->resizeColumnsToContents();
            count++;
            ii++;
            }

            showwindow->show();
            this->close();
            delete[] arr;
}

void inputOverHours::on_pushButton_rate_clicked()
{
    emit firstWindow();
    QWidget *showwindow = new QWidget();
    auto arr = new Employee[employees.getSize()];
        for (int i = 0; i < employees.getSize(); ++i) {
            arr[i] = employees[i];
        }
        merge_sort(arr, employees.getSize(), compareRate);
        showwindow->setWindowTitle("Отсортированный список сотрудников");
        showwindow->setGeometry(QRect(450, 150, 850, 200));
        showwindow->resize(750, 500);

        QTableWidget *tableWidget = new QTableWidget();
        QGridLayout *layout = new QGridLayout(showwindow);
        layout->addWidget(tableWidget, 0, 0);

        tableWidget->setColumnCount(6);
        tableWidget->setShowGrid(true);

        QStringList headers1;
                headers1.append("Фамилия");
                headers1.append("Имя");
                headers1.append("Отчество");
                headers1.append("Табельный номер");
                headers1.append("Количество проработнных за месяц часов");
                headers1.append("Почасовой тариф");
        tableWidget->setHorizontalHeaderLabels(headers1);

        tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);

        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

        int count = 0, ii = 0;
        for (int i = 0; i < employees.getSize(); i++) {
            employees[i] = arr[i];
            tableWidget->insertRow(ii);
            tableWidget->setItem(ii, 0, new QTableWidgetItem(employees[i].getSurname()));
            tableWidget->setItem(ii, 1, new QTableWidgetItem(employees[i].getName()));
            tableWidget->setItem(ii, 2, new QTableWidgetItem(employees[i].getPatronymicName()));
            tableWidget->setItem(ii, 3, new QTableWidgetItem(employees[i].getTabelNumber()));
            tableWidget->setItem(ii, 4, new QTableWidgetItem(QString::number(employees[i].getHoursWorked())));
            tableWidget->setItem(ii, 5, new QTableWidgetItem(QString::number(employees[i].getRate())));
            tableWidget->resizeColumnsToContents();
            count++;
            ii++;
        }

        showwindow->show();
        this->close();
        delete[] arr;
}
