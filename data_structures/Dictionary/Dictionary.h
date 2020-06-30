#pragma once
#include "LinkedList.h"
#include <iostream>
using namespace std;

class Dictionary
{
public:
	Dictionary();
	void add(pair<string, int> p);
	bool remove(string key);
	int getSize();
	pair<bool, int> getValue(string key);
	bool setValue(pair<string, int> p);
	~Dictionary();
private:
	float load_factor;
	int number_of_free_cells;
	int number_of_elements;
	int size;
	int prime;
	LinkedList **hashTable;
	int64_t hash(string s);
	void rehashing();
};

