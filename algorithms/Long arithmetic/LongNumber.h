#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <stdexcept>

using namespace std;

class LongNumber {
private:
    static const long long MaxDig = 100000;        // ������������ ���������� ����
    static const int osn = 1000;                // ��������� ����� ������� ���������
    vector<int> number;                            // � ������� number �������� �������� ������� �����
    LongNumber(const vector<int> &number);            // �����������
    void read(string arr);                        // ���������� ����� arr � ������ number
    void sub(const LongNumber &LN, int sp);    // �������� LN � ������ ������ sp
    bool moreOrEqual(const LongNumber &LN, int sp);

public:
    LongNumber(string number);            // ����������� 1
    LongNumber(int num);                // ����������� 2
    LongNumber(const LongNumber &LN);    // ����������� �����������
    ~LongNumber();                        // ����������

    friend ostream &operator<<(ostream &out, const LongNumber &LN);

    friend bool operator==(const LongNumber &left, const LongNumber &right);

    friend bool operator>(const LongNumber &left, const LongNumber &right);

    LongNumber &operator+=(const LongNumber &LN);

    friend LongNumber operator+(const LongNumber &left, const LongNumber &right);

    LongNumber &operator*=(const LongNumber &LN);

    friend LongNumber operator*(const LongNumber &left, const LongNumber &right);

    LongNumber &operator-=(const LongNumber &LN);

    friend LongNumber operator-(const LongNumber &left, const LongNumber &right);

    LongNumber &operator/=(const LongNumber &LN);

    friend LongNumber operator/(const LongNumber &left, const LongNumber &right);

    LongNumber &operator%=(const LongNumber &LN);

    friend LongNumber operator%(const LongNumber &left, const LongNumber &right);

    LongNumber &operator+=(char *number);

    friend LongNumber operator+(const LongNumber &left, char *number);

    LongNumber &operator*=(char *number);

    friend LongNumber operator*(const LongNumber &left, char *number);

    LongNumber &operator-=(char *number);

    friend LongNumber operator-(const LongNumber &left, char *number);

    LongNumber &operator/=(char *number);

    friend LongNumber operator/(const LongNumber &left, char *number);

    LongNumber &operator%=(char *number);

    friend LongNumber operator%(const LongNumber &left, char *number);
};
