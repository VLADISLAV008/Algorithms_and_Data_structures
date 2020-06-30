/*************************************
*			Week 2 lesson:			 *
* Implementing a Doubly Linked List  *
**************************************/

#include <iostream>
#include "DoublyLinkedList.h"

using namespace std;

/*
* Initializes the list to empty creating a dummy header node.
*/
DoublyLinkedList::DoublyLinkedList() {
    first = new Node;
    end = new Node;
    first->next = NULL;
    end->previous = NULL;
}

/*
* Destructor. Deallocates all the nodes of the linked list,
* including the header node.
*/
DoublyLinkedList::~DoublyLinkedList() {
    Node *temp1;
    while (first != NULL) {
        temp1 = first;
        first = first->next;
        delete temp1;
    }
}

/*
* Determines whether the list is empty.
*
* Returns true if the list is empty, false otherwise.
*/
bool DoublyLinkedList::isEmpty() {
    return first->next == NULL;
}

/*
* Prints the list elements.
*/
void DoublyLinkedList::display() {
    Node *current = first->next;

    while (current != NULL) {
        cout << current->info << " ";
        current = current->next;
    }

    cout << endl;
}

/*
* Prints the list elements from the last item to the first one
*/
void DoublyLinkedList::displayInReverse() {
    Node *current = end->previous;

    while (current != NULL) {
        cout << current->info << " ";
        current = current->previous;
    }

    cout << endl;
}

/*
* Adds the element x to the beginning of the list.
*
* x: element to be added to the list.
*/
void DoublyLinkedList::addBegin(int x) {
    Node *p = new Node;

    p->info = x;
    p->next = first->next;
    p->previous = NULL;
    if (isEmpty())
        end->previous = p;
    else
        (first->next)->previous = p;
    first->next = p;
}

/*
* Adds the element x to the end of the list.
*
* x: element to be added to the list.
*/
void DoublyLinkedList::addEnd(int x) {
    Node *p = new Node;

    p->info = x;
    p->next = NULL;
    p->previous = end->previous;
    if (isEmpty())
        first->next = p;
    else
        (end->previous)->next = p;

    end->previous = p;
}

/*
* Removes the first occurrence of x from the list. If x is not found,
* the list remains unchanged.
*
* x: element to be removed from the list.
*/
void DoublyLinkedList::remove(int x) {
    Node *old = first->next,
            *p = first;

    //Finding the address of the node before the one to be deleted
    bool found = false;
    while (old != NULL && !found) {
        if (old->info == x) found = true;
        else {
            p = old;
            old = p->next;
        }
    }

    //if x is in the list, remove it.
    if (found) {
        p->next = old->next;
        if (old->next != NULL) (old->next)->previous = p;
        else end->previous = p;
        delete old;
    }
}


