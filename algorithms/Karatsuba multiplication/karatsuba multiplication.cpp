#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

vector<int> create(string s) {
    vector<int> number;
    for (int i = s.length() - 1; i >= 0; --i)
        number.push_back(s[i] - '0');
    return number;
}

ostream &operator<<(ostream &out, const vector<int> number) {
    for (int i = number.size() - 1; i >= 0; --i)
        out << number[i];
    return out;
}

vector<int> mul(const vector<int> number1, const vector<int> number2) {
    vector<int> res;
    res.resize(number1.size() + number2.size(), 0);

    for (int i = 0; i < number1.size(); i++)
        for (int j = 0; j < number2.size(); j++) {
            res[i + j + 1] += (number1[i] * number2[j] + res[i + j]) / 10;
            res[i + j] = (number1[i] * number2[j] + res[i + j]) % 10;
        }
    int i = res.size() - 1;
    while (res[i] == 0 && i > 0) {
        res.pop_back();
        i--;
    }
    return res;
}

vector<int> add(const vector<int> num1, const vector<int> num2) {
    vector<int> number1 = num1, number2 = num2, res;

    int count = max(number1.size(), number2.size());
    number1.resize(count, 0);
    number2.resize(count, 0);
    res.resize(count + 1, 0);

    for (int i = 0; i < count; i++) {
        res[i + 1] = (number1[i] + number2[i] + res[i]) / 10;
        res[i] = (number1[i] + number2[i] + res[i]) % 10;
    }

    int i = res.size() - 1;
    while (i > 0 && res[i] == 0) {
        res.pop_back();
        i--;
    }
    return res;
}

vector<int> sub(const vector<int> number1, const vector<int> number2) {
    vector<int> number = number1;

    for (int i = 0; i < number2.size(); i++) {
        number[i] -= number2[i];
        int j = i;
        while (number[j] < 0 && j < number.size()) {
            number[j] += 10;
            number[j + 1]--;
            j++;
        }
    }

    int count = number.size() - 1;
    while (count > 0 && number[count] == 0) {
        number.pop_back();
        count--;
    }

    return number;
}

vector<int> karatsubaMul(const vector<int> xx, const vector<int> yy) {
    vector<int> x = xx, y = yy;
    int len = max(x.size(), y.size());
    if (len % 2 == 1)
        len++;
    x.resize(len);
    y.resize(len);

    int split = len / 2;

    if (split <= 6)
        return mul(xx, yy);

    vector<int> xRight, xLeft;
    for (int i = 0; i < split; ++i)
        xRight.push_back(x[i]);
    for (int i = split; i < len; ++i)
        xLeft.push_back(x[i]);

    vector<int> yRight, yLeft;
    for (int i = 0; i < split; ++i)
        yRight.push_back(y[i]);
    for (int i = split; i < len; ++i)
        yLeft.push_back(y[i]);

    vector<int> xSum = add(xLeft, xRight), ySum = add(yLeft, yRight);

    vector<int> product1, product2, product3;
    product1 = karatsubaMul(xLeft, yLeft);
    product2 = karatsubaMul(xRight, yRight);
    product3 = karatsubaMul(xSum, ySum);

    product3 = sub(sub(product3, product1), product2);

    vector<int> ans1, ans3;
    for (int i = 0; i < product1.size() + len; i++) {
        if (i < len)
            ans1.push_back(0);
        else
            ans1.push_back(product1[i - len]);
    }

    for (int i = 0; i < product3.size() + split; i++) {
        if (i < split)
            ans3.push_back(0);
        else
            ans3.push_back(product3[i - split]);
    }

    vector<int> res = add(add(ans1, ans3), product2);
    return res;
}

int main() {
    vector<int> number1 = create("8711129198194917883527844183686122989894424943636426448417394566");
    vector<int> number2 = create("2924825637132661199799711722273977411715641477832758942277358764");

    cout << number1 << endl;
    cout << number2 << endl;
    cout << karatsubaMul(number1, number2) << endl;
    system("pause");
    return 0;
}



