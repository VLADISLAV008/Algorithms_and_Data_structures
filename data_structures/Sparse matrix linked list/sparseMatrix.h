#pragma once
#include <iostream>
#include <string>
#include "rowOfMatrix.h"
using namespace std;

/* Linked list node.*/
struct Node
{
	int row;				// the number of row of the element stored in this node
	rowOfMatrix* rowMatrix;	// the row of matrix
	Node *next;				// link to next node
	Node() { rowMatrix = nullptr, next = nullptr; };
	Node(int row);
};

class sparseMatrix
{
public:
	sparseMatrix(int size);		              // Constructor
	sparseMatrix(const sparseMatrix& matrix); // Constructor copy
	~sparseMatrix();
	void insert(int value, int row, int column);
	friend ostream& operator<<(ostream& out, const sparseMatrix& matrix);

	sparseMatrix& operator+=(const sparseMatrix& matrix);
	friend sparseMatrix operator + (const sparseMatrix& matrixLeft, const sparseMatrix& matrixRight);
	sparseMatrix& operator-=(const sparseMatrix& matrix);
	friend sparseMatrix operator - (const sparseMatrix& matrixLeft, const sparseMatrix& matrixRight);
	sparseMatrix& operator*=(const sparseMatrix& matrix);
	friend sparseMatrix operator * (const sparseMatrix& matrixLeft, const sparseMatrix& matrixRight);
private:
	Node *first;	//pointer to header (dummy) node
	int size;
};

