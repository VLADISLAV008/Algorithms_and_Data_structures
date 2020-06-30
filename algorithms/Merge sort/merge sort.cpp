#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

void Merge(int *arr, int l, int m, int r) {
    cout << "Hi" << endl;
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temp arrays */
    int L[100000], R[10000];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void MergeSort(int *arr, int left, int right) {
    int midpoint;
    if (left < right) {
        midpoint = (left + right) / 2;
        MergeSort(arr, left, midpoint);
        MergeSort(arr, midpoint + 1, right);
        Merge(arr, left, midpoint, right);
    }
}

int main() {

    int A;
    int B;
    cin >> A >> B;
    int items1[1000];
    int items2[1000];
    for (int i = 0; i < A; i++) {
        cin >> items1[i];
    }
    for (int i = 0; i < B; i++) {
        cin >> items2[i];
    }
    MergeSort(items1, 0, A - 1);
    MergeSort(items2, 0, B - 1);

    return 0;
}