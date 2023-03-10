#include "computing.h"

Computing::Computing()
{
   aValue = 0;
   bValue = 0;
   cValue = 0;
   dValue = 0;
   eValue = 0;
   infixExpression = "";
   postfixExpression = "";
}

Computing::Computing(const QString& expr)
{
    infixExpression = expr;
    postfixExpression = toPostfixExpression();
}

extern QVector<Computing> expressions;

void Computing::setVariables (double a, double b, double c, double d, double e) {
    this->aValue = a;
    this->bValue = b;
    this->cValue = c;
    this->dValue = d;
    this->eValue = e;
}

void Computing::setExpressions(QString infixExpression) {
    this->infixExpression = infixExpression;
    this->postfixExpression = toPostfixExpression();
}

double Computing::getValueA() const {
    return this->aValue;
}

double Computing::getValueB() const {
    return this->bValue;
}

double Computing::getValueC() const {
    return this->cValue;
}

double Computing::getValueD() const {
    return this->dValue;
}

double Computing::getValueE() const {
    return this->eValue;
}

QString Computing::getPostfixExpression() const {
    return this->postfixExpression;
}

QString Computing::getInfixExpression() const {
    return this->infixExpression;
}

int operationPriority(QChar operation) {
    if (operation == '*' || operation == '/') return 3;
    else if (operation == '+' || operation == '-') return 2;
    else if (operation == '(') return 1;
    else return 0;
}

QString Computing::toPostfixExpression() {
    QString res;
        stack<QChar> operators;
        for (int i = 0; i < infixExpression.length(); i++) {
            if (infixExpression[i].isLetter()) {
                res.push_back(infixExpression[i]);
            }
            else if (infixExpression[i] == '+' || infixExpression[i] == '-' || infixExpression[i] == '*' || infixExpression[i] == '/') {
                if (!operators.size()) {
                    operators.push(infixExpression[i]);
                }
                else {
                    while ((operationPriority(infixExpression[i]) <= operationPriority(operators.top()))) {
                        res.push_back(operators.top());
                        operators.pop();
                        if (!operators.size())
                            break;
                    }
                    operators.push(infixExpression[i]);
                }
            }
            else if (infixExpression[i] == '(') {
                operators.push(infixExpression[i]);
            }
            else if (infixExpression[i] == ')') {
                while (operators.top() != '(') {
                    res.push_back(operators.top());
                    operators.pop();
                }
                operators.pop();
            }
        }
        while (operators.size()) {
            res.push_back(operators.top());
            operators.pop();
        }
        return res;
}

double Computing::computing() {
    stack<double> stack;
        for (int i = 0; i < postfixExpression.length(); i++) {
            if (postfixExpression[i] == 'a')
                stack.push(aValue);
            else if (postfixExpression[i] == 'b')
                stack.push(bValue);
            else if (postfixExpression[i] == 'c')
                stack.push(cValue);
            else if (postfixExpression[i] == 'd')
                stack.push(dValue);
            else if (postfixExpression[i] == 'e')
                stack.push(eValue);
            else if (postfixExpression[i] == '+') {
                double n1 = stack.top();
                stack.pop();
                double n2 = stack.top();
                stack.pop();
                stack.push(n1 + n2);
            }
            else if (postfixExpression[i] == '-') {
                double n1 = stack.top();
                stack.pop();
                double n2 = stack.top();
                stack.pop();
                stack.push(n2 - n1);
            }
            else if (postfixExpression[i] == '*') {
                double n1 = stack.top();
                stack.pop();
                double n2 = stack.top();
                stack.pop();
                stack.push(n1 * n2);
            }
            else if (postfixExpression[i] == '/') {
                double n1 = stack.top();
                stack.pop();
                double n2 = stack.top();
                stack.pop();
                stack.push(n2 / n1);
            }
        }
        return stack.top();
}

void GetAnotherExptessions() {
    QFile file("C:\\FilesForQtLabs\\Expressions.txt");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream file1(&file);
        int i = 0;
        while (!file1.atEnd()) {
            Computing expr;
            QString str;
            file1.readLineInto(&str);
            expr.setExpressions(str);
            double a, b, c, d, e;
            file1 >> a >> b >> c >> d >> e;
            expr.setVariables(a, b, c, d, e);
            expressions.push_back(expr);
            file1.readLineInto(&str);
        }
        file.close();
}
