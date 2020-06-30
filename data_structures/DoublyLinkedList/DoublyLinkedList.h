#pragma once
/*************************************
*			Week 2 lesson:			 *
* Implementing a Doubly Linked List  *
**************************************/

/*
* Doubly linked list node.
*/
struct Node
{
	int info;		//element stored in this node
	Node *next;		//link to next node
	Node *previous;	//link to previous node
};

/*
* Class implementing a linked list.
*/
class DoublyLinkedList
{
public:
	DoublyLinkedList();
	~DoublyLinkedList();
	bool isEmpty();
	void display();
	void displayInReverse();
	void addBegin(int);
	void addEnd(int x);
	void remove(int);

private:
	Node *first;	//pointer to header (dummy) node
	Node *end;		//pointer to the final (dummy) node
};

