#ifndef COMPUTING_H
#define COMPUTING_H
#include <QString>
#include "Stack.cpp"
#include <QDebug>
#include <algorithm>
#include <QFile>
#include <QTextStream>
#include "List.cpp"

class Computing
{
    double aValue;

    double bValue;

    double cValue;

    double dValue;

    double eValue;

    QString infixExpression;

    QString postfixExpression;

    QString toPostfixExpression();

public:
    Computing();

    Computing(const QString& expr);

    void setVariables (double, double, double, double, double);

    void setExpressions(QString);

    double getValueA() const;

    double getValueB() const;

    double getValueC() const;

    double getValueD() const;

    double getValueE() const;

    QString getPostfixExpression() const;

    QString getInfixExpression() const;

    double computing();

};

void GetAnotherExptessions();

#endif // COMPUTING_H
