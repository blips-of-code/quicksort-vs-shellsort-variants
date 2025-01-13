//---------------------------------------------------------------------

// Name: Sharmin Zaman

// Project: Programming Assignment 6 Part 1 - CS 321

// Purpose: To develop a program that tests out

// different variations of quicksort on several

// sizes of arrays

// Date: 4/21/2023

//---------------------------------------------------------------------
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

template<class T>
void quicksort_with_pivot (T data[], int first, int last) { //uses a randomly chosen element from within the portion of the array currently being sorted
    int lower = first+1, upper = last;
    swap(data[first],data[(first+last)/2]);
    T bound = data[first];
    while (lower <= upper) {
        while (bound > data[lower])
            lower++;
        while (bound < data[upper])
            upper--;
        if (lower < upper)
            swap(data[lower++],data[upper--]);
        else lower++;
    }
    swap(data[upper],data[first]);
    if (first < upper-1)
        quicksort_with_pivot(data,first,upper-1);
    if (upper+1 < last)
        quicksort_with_pivot(data,upper+1,last);
}

template<class T>
void quicksort_median (T data[], int first, int last) { //uses a median element of the first, middle, and last elements of the portion of the array currently being sorted
    if (first < last) {
        // Find median of first, middle, and last elements
        int mid = (first + last) / 2;
        if (data[first] > data[mid])
            swap(data[first], data[mid]);
        if (data[mid] > data[last])
            swap(data[mid], data[last]);
        if (data[first] > data[mid])
            swap(data[first], data[mid]);

        // Use median as pivot element
        T pivot = data[mid];

        // Partition the array around the pivot
        int i = first;
        int j = last;
        while (i <= j) {
            while (data[i] < pivot) i++;
            while (data[j] > pivot) j--;
            if (i <= j) {
                swap(data[i], data[j]);
                i++;
                j--;
            }
        }

        // Recursively sort the two partitions
        if (first < j)
            quicksort_median(data, first, j);
        if (i < last)
            quicksort_median(data, i, last);
    }
}

template<class T> //original quicksort function
void quicksort(T data[], int n) {
    quicksort_with_pivot(data, 0, n - 1);
}

int main() {
    // example usage with original pivot technique
    srand(time(nullptr)); // seed the random number generator with current time
    int arr[20]; //you basically change the number in here...
    for (int & i : arr) {
        i = rand() % 500000; // generate a random integer between 0 and 500000
    }

    cout << "Array before sorting: ";
    for (int i : arr)
        cout << i << " ";
    auto start = steady_clock::now();
    quicksort(arr, 20); //...and the value of n here
    auto stop = steady_clock::now();

    cout << "\nSorted array using original technique: ";
    for (int i : arr)
        cout << i << " ";
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nTime for original technique: " << fixed << duration.count()/1000.0 << " milliseconds" << endl;

    // example usage with random pivot technique
    int arr1[20];
    for (int & i : arr1) {
        i = rand() % 500000; // random integer between 0 and 99
    }
    cout << "\nArray before sorting: ";
    for (int i : arr1)
        cout << i << " ";

    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    auto start1 = steady_clock::now();
    quicksort_with_pivot(arr1, 0, n1-1); // Using random pivot technique
    auto stop1 = steady_clock::now();
    cout << "\nSorted array using random pivot technique: ";
    for (int i = 0; i < n1; i++)
        cout << arr1[i] << " ";
    auto duration1 = duration_cast<microseconds>(stop1 - start1);
    cout << "\nTime for random pivot technique: " << fixed << duration1.count()/1000.0 << " milliseconds" << endl;

    // example usage with median pivot technique
    int arr2[20];
    for (int & i : arr2) {
        i = rand() % 500000; // random integer between 0 and 99
    }
    cout << "\nArray before sorting: ";
    for (int i : arr2)
        cout << i << " ";
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    auto start2 = steady_clock::now();
    quicksort_median(arr2, 0, n2-1); // Using median pivot technique
    auto stop2 = steady_clock::now();
    cout << "\nSorted array using median pivot technique: ";
    for (int i = 0; i < n2; i++)
        cout << arr2[i] << " ";
    auto duration2 = duration_cast<microseconds>(stop2 - start2);
    cout << "\nTime for median pivot technique: " << fixed << duration2.count()/1000.0 << " milliseconds" << endl;

    return 0;
}