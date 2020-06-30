#pragma once
#include <string>
using namespace std;

class rowOfMatrix
{
public:
	rowOfMatrix(int size);				 // Constructor
	rowOfMatrix(const rowOfMatrix& row); // Constructor copy
	~rowOfMatrix();
	void insert(int value, int column);
	string toString() const;
	rowOfMatrix& operator+=(const rowOfMatrix& row);
	void changedSignOfAllValues();
	int getValue(int column);
private:
	/* Linked list node.*/
	struct Node
	{
		int value;		// the value stored in this node
		int column;		// the column of the element of the matrix stored in this node
		Node *next;		// link to next node
		Node() { next = nullptr; };
		Node(int value, int column, Node *next = nullptr);
	};
	Node *first;	//pointer to header (dummy) node
	int size;
};
