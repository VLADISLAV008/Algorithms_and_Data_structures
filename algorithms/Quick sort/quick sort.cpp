#include <iostream>
#include <vector>

using namespace std;

/**
* Quick-sorts this ArrayList.
*/
void quickSort(vector<int> list) {
    quicksort(list, 0, length - 1);
}

/**
* Recursive quickSort algorithm.
*
* begin: initial index of sublist to be quick-sorted.
* end: last index of sublist to be quick-sorted.
*/
void quickSort(vector<int> list, int begin, int end) {
    int temp;
    int pivot = findPivotLocation(begin, end);

    // swap list[pivot] and list[end]
    temp = list[pivot];
    list[pivot] = list[end];
    list[end] = temp;

    pivot = end;

    int i = begin,
            j = end - 1;

    bool iterationCompleted = false;
    while (!iterationCompleted) {
        while (list[i] < list[pivot])
            i++;
        while ((j >= 0) && (list[pivot] < list[j]))
            j--;

        if (i < j) {
            //swap list[i] and list[j]
            temp = list[i];
            list[i] = list[j];
            list[j] = temp;

            i++;
            j--;
        } else
            iterationCompleted = true;
    }

    //swap list[i] and list[pivot]
    temp = list[i];
    list[i] = list[pivot];
    list[pivot] = temp;

    if (begin < i - 1)
        quicksort(list, begin, i - 1);
    if (i + 1 < end)
        quicksort(list, i + 1, end);
}

/**
* Computes the pivot location.
*/
int findPivotLocation(int b, int e) {
    return (b + e) / 2;
}

