#include <iostream>
#include "Dictionary.h"

using namespace std;

int main() {
    Dictionary dict = Dictionary();
    for (int i = 0; i <= 100; i++) {
        dict.add(make_pair(to_string(i), i));
    }
    cout << dict.getSize() << endl;
    pair<bool, int> p = dict.getValue("55");
    if (p.first)
        cout << p.second << endl;
    if (dict.setValue(make_pair("55", 56))) {
        pair<bool, int> p = dict.getValue("55");
        if (p.first)
            cout << p.second << endl;
    }

    system("pause");
    return 0;
}