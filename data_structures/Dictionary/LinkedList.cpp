#include "LinkedList.h"

LinkedList::Node::Node(pair<string, int> item) {
    this->item = item;
    next = nullptr;
}

LinkedList::LinkedList() {
    this->first = new Node();
    size = 0;
}

void LinkedList::insert(pair<string, int> p) {
    Node *newNode = new Node(p);
    newNode->next = this->first->next;
    first->next = newNode;
    size++;
}

pair<bool, int> LinkedList::find(string key) {
    Node *node = first->next;
    while (node != nullptr) {
        if (node->item.first == key)
            return make_pair(true, node->item.second);
        node = node->next;
    }
    return make_pair(false, 0);
}

bool LinkedList::isEmpty() {
    return size == 0;
}

pair<string, int> LinkedList::getItem(int index) {
    if (index < size) {
        int i = 0;
        Node *node = first->next;
        while (i != index) {
            node = node->next;
            i++;
        }
        return node->item;
    }
    return pair<string, int>();
}

bool LinkedList::setItem(pair<string, int> item) {
    Node *node = first->next;
    while (node != nullptr) {
        if (node->item.first == item.first) {
            node->item.second = item.second;
            return true;
        }
        node = node->next;
    }
    return false;
}

bool LinkedList::remove(string key) {
    Node *node = first->next;
    Node *previous_node = first;
    while (node != nullptr) {
        if (node->item.first == key) {
            previous_node->next = node->next;
            delete node;
            size--;
            return true;
        }
        node = node->next;
        previous_node = previous_node->next;
    }
    return false;
}


LinkedList::~LinkedList() {
    Node *temp;
    while (first != nullptr) {
        temp = first;
        first = first->next;
        delete temp;
    }
}


