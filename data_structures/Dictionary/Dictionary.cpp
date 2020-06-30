#include "Dictionary.h"

Dictionary::Dictionary() {
    size = 10;
    load_factor = 0;
    number_of_elements = 0;
    number_of_free_cells = size;
    prime = 37;
    hashTable = new LinkedList *[size];
    for (int i = 0; i < size; ++i)
        hashTable[i] = new LinkedList();
}

void Dictionary::add(pair<string, int> p) {
    int index = hash(p.first) % size;
    number_of_elements++;
    if (hashTable[index]->isEmpty())
        number_of_free_cells--;
    hashTable[index]->insert(p);
    load_factor = (float) number_of_elements / number_of_free_cells;
    if (load_factor >= 0.8)
        rehashing();
}

bool Dictionary::remove(string key) {
    int index = hash(key) % size;
    bool result = hashTable[index]->remove(key);
    if (result) {
        number_of_elements--;
        if (hashTable[index]->getSize() == 0)
            number_of_free_cells--;
        load_factor = (float) number_of_elements / number_of_free_cells;
    }
    return result;
}

int Dictionary::getSize() {
    return size;
}

pair<bool, int> Dictionary::getValue(string key) {
    int index = hash(key) % size;
    return hashTable[index]->find(key);
}

bool Dictionary::setValue(pair<string, int> p) {
    int index = hash(p.first) % size;
    return hashTable[index]->setItem(p);
}


Dictionary::~Dictionary() {
    for (int i = 0; i < size; ++i)
        delete hashTable[i];
    delete[] hashTable;
}

int64_t Dictionary::hash(string s) {
    int64_t prime_power = 1;
    int64_t ans = 0;
    for (int i = 0; i < s.length(); ++i) {
        ans += abs((s[i] - '0' + 1) * prime_power);
        prime_power *= prime;
    }
    return ans;
}

void Dictionary::rehashing() {
    size *= 2;
    number_of_free_cells = size;
    LinkedList **newHashTable = new LinkedList *[size];
    for (int i = 0; i < size; ++i)
        newHashTable[i] = new LinkedList();
    for (int i = 0; i < size / 2; ++i)
        for (int j = 0; j < hashTable[i]->getSize(); ++j) {
            pair<string, int> p = hashTable[i]->getItem(j);
            int index = hash(p.first) % size;
            if (newHashTable[index]->isEmpty())
                number_of_free_cells--;
            newHashTable[index]->insert(p);
        }
    for (int i = 0; i < size / 2; ++i)
        delete hashTable[i];
    delete[] hashTable;
    hashTable = newHashTable;
    load_factor = (float) number_of_elements / number_of_free_cells;
}
