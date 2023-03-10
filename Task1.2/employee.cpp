#include "employee.h"

Employee::Employee()
{
    this->name = "";
    this->surname = "";
    this->patronymicName = "";
    this->tabelNumber = "";
    this->hoursWorked = 0;
    this->rate = 0;
}

void Employee::setName(QString name) {
    this->name = name;
}

void Employee::setSurname(QString surname){
    this->surname = surname;
}

void Employee::setPatronymicName(QString patronymicName) {
    this->patronymicName = patronymicName;
}

void Employee::setTabelNumber(QString tabelNumber) {
    this->tabelNumber = tabelNumber;
}

void Employee::setHoursWorked(int hoursWorked) {
    this->hoursWorked = hoursWorked;
}

void Employee::setRate(double rate) {
    this->rate = rate;
}

QString Employee::getName() {
    return name;
}

QString Employee::getSurname() {
    return surname;
}

QString Employee::getPatronymicName() {
    return patronymicName;
}

QString Employee::getTabelNumber() {
    return tabelNumber;
}

int Employee::getHoursWorked() {
    return hoursWorked;
}

double Employee::getRate() {
    return rate;
}
