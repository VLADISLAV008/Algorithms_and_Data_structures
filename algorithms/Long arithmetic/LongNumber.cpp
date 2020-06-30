#include "LongNumber.h"

LongNumber::LongNumber(string arr) {
    read(arr);
}

LongNumber::LongNumber(const vector<int> &number) {
    this->number = number;
}

LongNumber::LongNumber(int num) {
    string ans = to_string(num);
    read(ans);
}

LongNumber::LongNumber(const LongNumber &LN) {
    for (int i = 0; i < LN.number.size(); i++) {
        this->number.push_back(LN.number[i]);
    }
}

void LongNumber::sub(const LongNumber &LN, int sp) {
    for (int i = 0; i < LN.number.size(); i++) {
        number[i + sp] -= LN.number[i];
        int j = i;
        while (number[j + sp] < 0 && j < number.size()) {
            number[j + sp] += osn;
            number[j + sp + 1]--;
            j++;
        }
    }

    int count = number.size() - 1;
    while (count > 0 && number[count] == 0) {
        number.pop_back();
        count--;
    }
}

bool LongNumber::moreOrEqual(const LongNumber &LN, int sp) {
    LongNumber zeros = LongNumber(osn);
    LongNumber num = LongNumber(LN);

    for (int i = 0; i < sp; i++)
        num *= zeros;

    if (*this > num)
        return true;
    else {
        if (*this == num)
            return true;
        else
            return false;
    }
}

void LongNumber::read(string arr) {

    for (int j = 0; j < arr.length(); j++) {
        /*
            "�������������" ������� ����� � ����� �� number[i]
             � ������� ����� ����� �� number[i+1].
        */
        for (int i = number.size() - 1; i >= 0; i--) {
            long long value = number[i] * 10;

            if (i == number.size() - 1) {
                if (value / osn > 0)
                    number.push_back(value / osn);
            } else
                number[i + 1] += value / osn;
            number[i] = value % osn;
        }

        /*��������� ������� ����� � ����� �� number[0]*/
        if (number.size() == 0)
            number.push_back(arr[j] - '0');
        else
            number[0] += arr[j] - '0';
    }
}

LongNumber::~LongNumber() {
}

ostream &operator<<(ostream &out, const LongNumber &LN) {
    string s, ls;
    ls = to_string(LN.osn / 10);
    out << LN.number[LN.number.size() - 1];

    for (int i = LN.number.size() - 2; i >= 0; i--) {
        s = to_string(LN.number[i]);
        while (s.length() < ls.length())
            s = '0' + s;
        out << s;
    }

    return out;
}

bool operator==(const LongNumber &left, const LongNumber &right) {
    bool eq = false;
    if (left.number.size() == right.number.size()) {
        int i = 0;
        while (i < left.number.size() && left.number[i] == right.number[i])
            i++;
        if (i == left.number.size() + 1)
            eq = true;
    }
    return eq;
}

bool operator>(const LongNumber &left, const LongNumber &right) {
    bool more = false;
    if (left.number.size() < right.number.size()) return false;
    if (left.number.size() > right.number.size()) return true;
    else {
        int i = left.number.size() - 1;
        while (i >= 0 && left.number[i] == right.number[i])
            i--;
        if (i == -1)
            return false;
        else if (left.number[i] > right.number[i])
            return true;
        else
            return false;
    }
}

LongNumber &LongNumber::operator+=(const LongNumber &LN) {
    int count = max(number.size(), LN.number.size());
    LongNumber lN(LN);

    vector<int> res;
    number.resize(count, 0);
    lN.number.resize(count, 0);
    res.resize(count + 1, 0);

    for (int i = 0; i < count; i++) {
        res[i + 1] = (number[i] + lN.number[i] + res[i]) / osn;
        res[i] = (number[i] + lN.number[i] + res[i]) % osn;
    }

    int i = res.size() - 1;
    while (i > 0 && res[i] == 0) {
        res.pop_back();
        i--;
    }

    number = res;
    return *this;
}

LongNumber operator+(const LongNumber &left, const LongNumber &right) {
    LongNumber ans(left);
    return ans += right;
}

LongNumber &LongNumber::operator-=(const LongNumber &LN) {
    sub(LN, 0);
    return *this;
}

LongNumber operator-(const LongNumber &left, const LongNumber &right) {
    LongNumber ans = LongNumber(left);
    return ans -= right;
}

LongNumber &LongNumber::operator*=(const LongNumber &LN) {
    vector<int> res;
    res.resize(number.size() + LN.number.size(), 0);

    for (int i = 0; i < number.size(); i++)
        for (int j = 0; j < LN.number.size(); j++) {
            res[i + j + 1] += (number[i] * LN.number[j] + res[i + j]) / osn;
            res[i + j] = (number[i] * LN.number[j] + res[i + j]) % osn;
        }

    int i = res.size() - 1;
    while (res[i] == 0 && i > 0) {
        res.pop_back();
        i--;
    }

    number = res;
    return *this;
}

LongNumber operator*(const LongNumber &left, const LongNumber &right) {
    LongNumber ans = LongNumber(left);
    return ans *= right;
}

LongNumber &LongNumber::operator/=(const LongNumber &LN) {
    if (LN == LongNumber(0)) {
        throw (runtime_error("Division by zero"));
    }
    vector<int> res;
    LongNumber ost(*this);

    if (*this > LN) {
        int sp = number.size() - LN.number.size();
        if (!moreOrEqual(LN, sp))
            sp--;
        res.resize(sp + 2, 0);
        while (sp >= 0) {
            int left = 0, right = osn;
            while (left < right - 1) {
                LongNumber middle((left + right) / 2);
                LongNumber product = LN * middle;
                if (ost.moreOrEqual(product, sp))
                    left = (left + right) / 2;
                else
                    right = (left + right) / 2;
            }
            LongNumber middle((left + right) / 2);
            LongNumber product = LN * middle;

            if (ost > product)
                ost.sub(product, sp);
            else {
                product.sub(ost, sp);
                ost.number = product.number;
            }
            res[sp] = (left + right) / 2;
            sp--;
        }
    } else {
        if (*this == LN)
            res[1] = 1;
        else
            ost = number;
    }

    int i = res.size() - 1;
    while (res[i] == 0 && i > 0) {
        res.pop_back();
        i--;
    }

    number = res;
    return *this;
}

LongNumber operator/(const LongNumber &left, const LongNumber &right) {
    LongNumber ans = LongNumber(left);
    return ans /= right;
}

LongNumber &LongNumber::operator%=(const LongNumber &LN) {
    if (LN == LongNumber(0)) {
        throw (runtime_error("Division by zero"));
    }
    vector<int> res;
    LongNumber ost(*this);

    if (*this > LN) {
        int sp = number.size() - LN.number.size();
        if (!moreOrEqual(LN, sp))
            sp--;

        res.resize(sp + 2, 0);
        while (sp >= 0) {
            int left = 0, right = osn;
            while (left < right - 1) {
                LongNumber middle((left + right) / 2);
                LongNumber product = LN * middle;
                if (ost.moreOrEqual(product, sp))
                    left = (left + right) / 2;
                else
                    right = (left + right) / 2;
            }
            LongNumber middle((left + right) / 2);
            LongNumber product = LN * middle;

            if (ost > product)
                ost.sub(product, sp);

            else {
                product.sub(ost, sp);
                ost.number = product.number;
            }
            res[sp] = (left + right) / 2;
            sp--;
        }
    } else {
        if (*this == LN)
            res[1] = 1;
        else
            ost = number;
    }

    int i = res.size() - 1;
    while (res[i] == 0 && i > 0) {
        res.pop_back();
        i--;
    }

    number = ost.number;
    return *this;
}

LongNumber operator%(const LongNumber &left, const LongNumber &right) {
    LongNumber ans = LongNumber(left);
    return ans %= right;
}

LongNumber &LongNumber::operator+=(char *number) {
    LongNumber right(number);
    *this += right;
    return *this;
}

LongNumber operator+(const LongNumber &left, char *number) {
    LongNumber ans(left);
    return ans += number;
}

LongNumber &LongNumber::operator-=(char *number) {
    LongNumber right(number);
    sub(right, 0);
    return *this;
}

LongNumber operator-(const LongNumber &left, char *number) {
    LongNumber ans = LongNumber(left);
    return ans -= number;
}

LongNumber &LongNumber::operator*=(char *number) {
    LongNumber right(number);
    *this *= right;
    return *this;
}

LongNumber operator*(const LongNumber &left, char *number) {
    LongNumber ans = LongNumber(left);
    return ans *= number;
}

LongNumber &LongNumber::operator/=(char *number) {
    LongNumber right(number);
    *this /= right;
    return *this;
}

LongNumber operator/(const LongNumber &left, char *number) {
    LongNumber ans = LongNumber(left);
    return ans /= number;
}

LongNumber &LongNumber::operator%=(char *number) {
    LongNumber right(number);
    *this %= right;
    return *this;
}

LongNumber operator%(const LongNumber &left, char *number) {
    LongNumber ans = LongNumber(left);
    return ans %= number;
}
