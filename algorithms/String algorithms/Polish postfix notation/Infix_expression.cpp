#include "Infix_expression.h"

/*
 * Default constructor.
 */
Infix_expression::Infix_expression() {}

/*
 * This function sets the data member by an infix expression.
 * The function first check if the infix expression is well formed and balanced
 * with brackets by calling  private member functions before passing it to the
 * data member. The function returns true if the operation is successfully
 * performed. Otherwise it returns false to indicate the parameter expression is
 * not valid.
 */
bool Infix_expression::setExpression(string exp) {
    if (checkBraces(exp) && validExpression(exp)) {
        this->expression = exp;
        return true;
    }
    return false;
}

/*
 * This function evaluates the expression stored in the data member.
 * The function first convert the infix expressionto its postfix form
 * and then evaluate the resulting postfix expression.
 */
int Infix_expression::evaluateExpression() {
    return evaluatePostfixExpression(toPostfixExpression(expression));
}

/*
 * Destructor.
 */
Infix_expression::~Infix_expression() {}

/*
 * The private member function that checks if an infix expression is well
 * formed.
 */
bool Infix_expression::validExpression(string exp) {
    if (!checkBraces(exp)) return false;
    bool prevOperand = false;
    bool prevOperator = false;
    char ch;
    for (int i = 0; i < exp.length(); i++) {
        ch = exp[i];
        if (i == 0) {
            if (ch == '*' || ch == '/') return false;
            if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
                prevOperator = true;
            } else
                prevOperator = false;
        } else {
            if ((ch == '+' || ch == '-' || ch == '*' || ch == '/')) {
                if (prevOperator) return false;
                prevOperator = true;
            } else {
                if (ch != ' ') prevOperator = false;
            }
        }
    }

    for (int i = 0; i < exp.length() - 2; i++) {
        if (exp[i] >= '0' && exp[i] <= '9' && exp[i + 1] == ' ' &&
            exp[i + 2] >= '0' && exp[i + 2] <= '9')
            return false;
    }

    return true;
}

/*
 * The private member function that checks for balanced brackets of an
 * expression.
 */
bool Infix_expression::checkBraces(string exp) {
    stack<char> stack;
    bool balancedSoFar = true;
    int i = 0;
    while (balancedSoFar && i < exp.length()) {
        char ch = exp[i];
        i++;
        // Push an open brace
        if (ch == '(') stack.push('(');
            // Close brace
        else if (ch == ')') {
            if (!stack.empty())
                stack.pop();  // Pop a matching open brace
            else            // No matching open brace
                balancedSoFar = false;
        }
    }
    if (balancedSoFar && stack.empty())
        return true;
    else
        return false;
}

/*
 * The private member function that converts an infix expression to a postfix
 * expression.
 */
string Infix_expression::toPostfixExpression(string exp) {
    stack<char> opstack;
    string answer;
    int i = 0;
    while (i < exp.length()) {
        char ch = exp[i];
        if (ch >= '0' && ch <= '9') {
            answer.push_back(ch);
            if (i != exp.length() - 1)
                while (exp[i + 1] >= '0' && exp[i + 1] <= '9') {
                    answer.push_back(exp[i + 1]);
                    i++;
                    if (i == exp.length() - 1) break;
                }
            answer.push_back(' ');
        } else {
            if (ch == '(') opstack.push(ch);
            if (ch == ')') {
                while (opstack.top() != '(') {
                    answer.push_back(opstack.top());
                    answer.push_back(' ');
                    opstack.pop();
                }
                opstack.pop();
            }
            if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
                if (!opstack.empty())
                    while (precedence(opstack.top()) >= precedence(ch)) {
                        answer.push_back(opstack.top());
                        answer.push_back(' ');
                        opstack.pop();
                        if (opstack.empty()) break;
                    }
                opstack.push(ch);
            }
        }
        i++;
    }
    while (!opstack.empty()) {
        answer.push_back(opstack.top());
        answer.push_back(' ');
        opstack.pop();
    }
    return answer;
}

/*
 * The private member function that determines the precedence of an operator.
 */
int Infix_expression::precedence(char ch) {
    if (ch == '*' || ch == '/') return 3;
    if (ch == '+' || ch == '-') return 2;
    if (ch == '(') return 1;
    return 0;
}

/*
 * The private member function that evaluates a postfix expression.
 */
int Infix_expression::evaluatePostfixExpression(string exp) {
    stack<int> mystack;
    int number;
    int i = 0;
    while (i < exp.length()) {
        char ch = exp[i];
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            int a = mystack.top();
            mystack.pop();

            int b = mystack.top();
            mystack.pop();
            int c;
            if (ch == '+') {
                int c = b + a;
                mystack.push(c);
            }
            if (ch == '-') {
                c = b - a;
                mystack.push(c);
            }
            if (ch == '*') {
                c = b * a;
                mystack.push(c);
            }
            if (ch == '/') {
                c = b / a;
                mystack.push(c);
            }
        } else {
            if (ch != ' ') {
                if (ch >= '0' && ch <= '9') {
                    number = ch - '0';
                    if (i != exp.length() - 1 && exp[i + 1] != ' ')
                        while (exp[i + 1] >= '0' && exp[i + 1] <= '9') {
                            number *= 10;
                            number += (exp[i + 1] - '0');
                            i++;
                            if (i == exp.length() - 1) break;
                        }
                    mystack.push(number);
                }
            }
        }
        i++;
    }

    return mystack.top();
}
