#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QString>

class Employee
{
private:
    QString name;

    QString surname;

    QString patronymicName;

    QString tabelNumber;

    int hoursWorked;

    double rate;

public:
    Employee();

    void setName(QString);

    void setSurname(QString);

    void setPatronymicName(QString);

    void setTabelNumber(QString);

    void setHoursWorked(int);

    void setRate(double);

    QString getName();

    QString getSurname();

    QString getPatronymicName();

    QString getTabelNumber();

    int getHoursWorked();

    double getRate();
};

#endif // EMPLOYEE_H
