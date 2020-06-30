#include "rowOfMatrix.h"

rowOfMatrix::Node::Node(int value, int column, Node *next) {
    this->value = value;
    this->column = column;
    this->next = next;
}

/*
* Initializes the list to empty creating a dummy header node.
*/
rowOfMatrix::rowOfMatrix(int size) {
    this->first = new Node();
    this->size = size;
}

rowOfMatrix::rowOfMatrix(const rowOfMatrix &row) {
    this->first = new Node();
    this->size = row.size;

    Node *current = row.first->next;
    while (current != nullptr) {
        insert(current->value, current->column);
        current = current->next;
    }
}

/*
* Destructor. Deallocates all the nodes of the linked list,
* including the header node.
*/
rowOfMatrix::~rowOfMatrix() {
    Node *temp;
    while (first != nullptr) {
        temp = first;
        first = first->next;
        delete temp;
    }
}

/*
* Adds the element to the linked list in descending order.
* If the element exist in this column then the value will be update (increase or decrease)
*
* Node of value, column: the element of the matrix to be added to the list.
*/
void rowOfMatrix::insert(int value, int column) {
    Node *newNode = new Node(value, column);
    Node *current = first->next, *prev = first;

    while (current != nullptr && current->column < column) {
        prev = prev->next;
        current = current->next;
    }

    if (current == nullptr) {
        prev->next = newNode;
    } else {
        if (current->column == column) {
            current->value += value;
            if (current->value == 0) {
                prev->next = current->next;
                delete current;
            }
            delete newNode;
        } else {
            prev->next = newNode;
            newNode->next = current;
        }
    }
}

string rowOfMatrix::toString() const {
    string result;
    int index = 1;
    Node *current = first->next;
    while (current != nullptr) {
        for (int i = index; i < current->column; i++)
            result.append("0 ");
        result.append(to_string(current->value));
        result.append(" ");
        index = current->column + 1;
        current = current->next;
    }
    for (int i = index; i <= size; i++)
        result.append("0 ");
    return result;
}

rowOfMatrix &rowOfMatrix::operator+=(const rowOfMatrix &row) {
    Node *current = row.first->next;
    while (current != nullptr) {
        insert(current->value, current->column);
        current = current->next;
    }

    return *this;
}

void rowOfMatrix::changedSignOfAllValues() {
    Node *current = first->next;
    while (current != nullptr) {
        current->value *= -1;
        current = current->next;
    }
}

int rowOfMatrix::getValue(int column) {
    Node *current = first->next;
    while (current != nullptr) {
        if (current->column == column)
            return current->value;
        current = current->next;
    }
    return 0;
}
