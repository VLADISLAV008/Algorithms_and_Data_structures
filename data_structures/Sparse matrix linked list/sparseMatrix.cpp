#include "sparseMatrix.h"

Node::Node(int row) {
    this->row = row;
    rowMatrix = nullptr;
    next = nullptr;
}

/*
* Initializes the list to empty creating a dummy header node.
*/
sparseMatrix::sparseMatrix(int size) {
    this->first = new Node();
    this->size = size;
}

sparseMatrix::sparseMatrix(const sparseMatrix &matrix) {
    this->first = new Node();
    this->size = matrix.size;
    Node *current = first;

    Node *currentMatrix = matrix.first->next;
    while (currentMatrix != nullptr) {
        Node *newNode = new Node(currentMatrix->row);
        newNode->rowMatrix = new rowOfMatrix(*currentMatrix->rowMatrix);
        current->next = newNode;
        currentMatrix = currentMatrix->next;
        current = current->next;
    }
}

/*
* Destructor. Deallocates all the nodes of the linked list,
* including the header node.
*/
sparseMatrix::~sparseMatrix() {
    Node *temp;
    while (first != nullptr) {
        temp = first;
        first = first->next;
        if (temp->rowMatrix != nullptr)
            delete temp->rowMatrix;
        delete temp;
    }
}

/*
* Adds the element to the linked list in descending order.
* If the element exist in this column then the value will be update (increase or decrease)
*
* Node of value, column: the element of the matrix to be added to the list.
*/
void sparseMatrix::insert(int value, int row, int column) {
    Node *newNode = new Node(row);
    newNode->rowMatrix = new rowOfMatrix(size);

    Node *current = first->next, *prev = first;

    while (current != nullptr && current->row < row) {
        prev = prev->next;
        current = current->next;
    }

    if (current == nullptr) {
        prev->next = newNode;
        newNode->rowMatrix->insert(value, column);
    } else {
        if (current->row == row) {
            current->rowMatrix->insert(value, column);
            delete newNode->rowMatrix;
            delete newNode;
        } else {
            newNode->next = current;
            prev->next = newNode;
            newNode->rowMatrix->insert(value, column);
        }
    }
}

ostream &operator<<(ostream &out, const sparseMatrix &matrix) {
    int index = 1;
    string empty;
    for (int i = 0; i < matrix.size; i++)
        empty.append("0 ");

    Node *current = matrix.first->next;
    while (current != nullptr) {
        for (int i = index; i < current->row; i++)
            out << empty << "\n";
        out << current->rowMatrix->toString() << "\n";
        index = current->row + 1;
        current = current->next;
    }
    for (int i = index; i <= matrix.size; i++)
        out << empty << "\n";

    return out;
}

sparseMatrix &sparseMatrix::operator+=(const sparseMatrix &matrix) {
    Node *current = first->next, *prev = first;
    Node *currentMatrix = matrix.first->next;
    while (currentMatrix != nullptr) {
        while (current != nullptr && current->row < currentMatrix->row) {
            prev = prev->next;
            current = current->next;
        }
        if (current != nullptr) {
            if (current->row == currentMatrix->row)
                *current->rowMatrix += *currentMatrix->rowMatrix;
            else {
                Node *newNode = new Node(currentMatrix->row);
                newNode->rowMatrix = new rowOfMatrix(*currentMatrix->rowMatrix);
                prev->next = newNode;
                newNode->next = current;
                prev = newNode;
            }
        } else {
            Node *newNode = new Node(currentMatrix->row);
            newNode->rowMatrix = new rowOfMatrix(*currentMatrix->rowMatrix);
            prev->next = newNode;
            prev = newNode;
        }
        currentMatrix = currentMatrix->next;
    }
    return *this;
}

sparseMatrix operator+(const sparseMatrix &matrixLeft, const sparseMatrix &matrixRight) {
    sparseMatrix ans(matrixLeft);
    return ans += matrixRight;
}

sparseMatrix &sparseMatrix::operator-=(const sparseMatrix &matrix) {
    sparseMatrix m(matrix);
    Node *current = m.first->next;
    while (current != nullptr) {
        current->rowMatrix->changedSignOfAllValues();
        current = current->next;
    }
    *this += m;
    return *this;
}

sparseMatrix &sparseMatrix::operator*=(const sparseMatrix &matrix) {
    sparseMatrix m(*this);
    Node *temp;
    while (first != nullptr) {
        temp = first;
        first = first->next;
        if (temp->rowMatrix != nullptr)
            delete temp->rowMatrix;
        delete temp;
    }
    this->first = new Node();

    Node *current = m.first->next, *prev = first;

    while (current != nullptr) {
        for (int column = 1; column <= size; column++) {
            Node *currentMatrix = matrix.first->next;
            while (currentMatrix != nullptr) {
                insert(currentMatrix->rowMatrix->getValue(column) * current->rowMatrix->getValue(currentMatrix->row),
                       current->row, column);
                currentMatrix = currentMatrix->next;
            }
        }
        current = current->next;
    }

    return *this;
}

sparseMatrix operator-(const sparseMatrix &matrixLeft, const sparseMatrix &matrixRight) {
    sparseMatrix ans(matrixLeft);
    return ans -= matrixRight;
}

sparseMatrix operator*(const sparseMatrix &matrixLeft, const sparseMatrix &matrixRight) {
    sparseMatrix ans(matrixLeft);
    return ans *= matrixRight;
}
