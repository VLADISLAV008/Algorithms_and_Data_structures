/******************************
*  Week 1 lab - exercise 1:   *
*   a simple ArrayList class  *
*******************************/

#include <iostream>
#include "ArrayList.h"

using namespace std;

/*
* Default constructor. Sets length to 0, initializing the list as an empty
* list. Default size of array is 20.
*/
ArrayList::ArrayList() {
    SIZE = 100;
    list = new int[SIZE];
    length = 0;
}

/*
* Destructor. Deallocates the dynamic array list.
*/
ArrayList::~ArrayList() {
    delete[] list;
    list = NULL;
}

/*
* Determines whether the list is empty.
*
* Returns true if the list is empty, false otherwise.
*/
bool ArrayList::isEmpty() {
    return length == 0;
}

/*
* Prints the list elements.
*/
void ArrayList::display() {
    for (int i = 0; i < length; i++)
        cout << list[i] << " ";
    cout << endl;
}

/*
* Adds the element x to the end of the list. List length is increased by 1.
*
* x: element to be added to the list
*/
void ArrayList::add(int x) {
    if (length == SIZE) {
        SIZE = 2 * SIZE;
        int *list1 = new int[SIZE];
        for (int i = 0; i < length; i++)
            list1[i] = list[i];
        delete[] list;
        list = list1;
        list[length] = x;
        length++;
    } else {

    }
}

/*
* Removes the element at the given location from the list. List length is
* decreased by 1.
*
* pos: location of the item to be removed
*/
void ArrayList::removeAt(int pos) {
    if (pos < 0 || pos >= length) {
        cout << "Removal Error: invalid position" << endl;
    } else {
        for (int i = pos; i < length - 1; i++)
            list[i] = list[i + 1];
        length--;
    }
}