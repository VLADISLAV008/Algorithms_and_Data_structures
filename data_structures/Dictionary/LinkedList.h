#pragma once
#include <string>
#include <iostream>
using namespace std;

class LinkedList
{
public:
	LinkedList();
	void insert(pair<string, int> p);
	pair<bool, int> find(string key);
	bool isEmpty();
	pair<string, int> getItem(int index);
	bool setItem(pair<string, int> p);
	bool remove(string key);
	int getSize() { return size; };
	~LinkedList();

private:
	/* Linked list node.*/
	struct Node
	{
		pair<string, int> item;
		Node* next;
		Node() { next = nullptr; }
		Node(pair<string, int> p);
	};
	int size;
	Node* first; //pointer to header (dummy) node
};

