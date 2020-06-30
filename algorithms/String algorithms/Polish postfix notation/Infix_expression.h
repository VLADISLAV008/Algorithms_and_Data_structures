#pragma once

#include <string>
#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;

/*
* A class that implements the calculation of an infix expression.
*/
class Infix_expression {
private:
    string expression;

    bool validExpression(string exp);

    bool checkBraces(string exp);

    string toPostfixExpression(string exp);

    int precedence(char ch);

    int evaluatePostfixExpression(string exp);

public:
    Infix_expression();

    bool setExpression(string exp);

    int evaluateExpression();

    ~Infix_expression();
};

