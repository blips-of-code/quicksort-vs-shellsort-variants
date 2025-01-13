//---------------------------------------------------------------------

// Name: Sharmin Zaman

// Project: Programming Assignment 6 Part 2 - CS 321

// Purpose: To develop a program that tests out

// different variations of shellsort on several

// sizes of arrays

// Date: 4/21/2023

//---------------------------------------------------------------------
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

template<class T>
void Shellsort_a(T data[], int n) { //a) original variant with stop added
    int i, j, hCnt, h;
    int increments[20], k;
    //create an appropriate number of increments h
    for (h = 1, i = 0; h < n; i++) {
        increments[i] = h;
        h = 3 * h + 1;
        if (h + 2 >= n) {
            break;
        }
    }
    // loop on the number of different increments h
    for (i--; i >= 0; i--) {
        h = increments[i];
        // loop on the number of subarrays h-sorted in ith pass
        for (hCnt = h; hCnt < 2*h; hCnt++) {
            // insertion sort for subarray containing every hth element of array data
            for (j = hCnt; j < n; ) {
                T tmp = data[j];
                k = j;
                while (k-h >= 0 && tmp < data[k-h]) {
                    data[k] = data[k-h];
                    k -= h;
                }
                data[k] = tmp;
                j += h;
            }
        }
    }
}
template<class T>
void Shellsort_b(T data[], int n) { //b) h = (2^k)-1 for k=1 up to the largest k for which (2^k)-1<n
    int i, j, hCnt, h, k;
    int increments[20];
    // calculate increments using h = (2^k)-1
    for (k = 1, h = 1; h < n; k++, h = (1 << k) - 1) {
        increments[k - 1] = h;
    }
    // loop on the number of different increments h
    for (k--; k >= 0; k--) {
        h = increments[k];
        // loop on the number of subarrays h-sorted in kth pass
        for (hCnt = h; hCnt < 2*h; hCnt++) {
            // insertion sort for subarray containing every hth element of array data
            for (j = hCnt; j < n; ) {
                T tmp = data[j];
                int p = j;
                while (p - h >= 0 && tmp < data[p - h]) {
                    data[p] = data[p - h];
                    p -= h;
                }
                data[p] = tmp;
                j += h;
            }
        }
    }
}
template<class T>
void Shellsort_c(T data[], int n) { //c) h1 = 1, then h = (2^k)+1 for k=1 up to the largest k
    int i, j, hCnt, h, k;
    int increments[20];
    // calculate increments using h1 = 1, then h = (2^k)+1
    for (k = 1, h = 1; h < n; k++, h = (1 << k) + 1) {
        increments[k - 1] = h;
    }
    // loop on the number of different increments h
    for (k--; k >= 0; k--) {
        h = increments[k];
        // loop on the number of subarrays h-sorted in kth pass
        for (hCnt = h; hCnt < 2*h; hCnt++) {
            // insertion sort for subarray containing every hth element of array data
            for (j = hCnt; j < n; ) {
                T tmp = data[j];
                int p = j;
                while (p - h >= 0 && tmp < data[p - h]) {
                    data[p] = data[p - h];
                    p -= h;
                }
                data[p] = tmp;
                j += h;
            }
        }
    }
}

template<class T>
void Shellsort_d(T data[], int n) { //d) Fibonacci numbers starting with F(2)=1 up to the largest F(k)<n
    int i, j, hCnt, h;
    int fib[30];
    fib[0] = 0; fib[1] = 1;
    // calculate Fibonacci numbers up to n
    for (i = 2; ; i++) {
        fib[i] = fib[i-1] + fib[i-2];
        if (fib[i] >= n) break;
    }
    // loop on the number of different increments h
    for (i--; i > 0; i--) {
        h = fib[i];
        // loop on the number of subarrays h-sorted in ith pass
        for (hCnt = h; hCnt < 2*h; hCnt++) {
            // insertion sort for subarray containing every hth element of array data
            for (j = hCnt; j < n; ) {
                T tmp = data[j];
                int k = j;
                while (k - h >= 0 && tmp < data[k - h]) {
                    data[k] = data[k - h];
                    k -= h;
                }
                data[k] = tmp;
                j += h;
            }
        }
    }
}

template<class T>
void Shellsort_e(T data[], int n) { //e) n/2 increment for first iteration, then hi=floor(0.75hi+1) until you reach 1
    int i, j, hCnt, h;
    h = n/2;
    while (h > 0) {
        for (hCnt = h; hCnt < 2*h && hCnt < n; hCnt++) {
            for (i = hCnt; i < n; ) {
                T tmp = data[i];
                for (j = i; j >= h && tmp < data[j-h]; j -= h) {
                    data[j] = data[j-h];
                }
                data[j] = tmp;
                i += h;
            }
        }
        h = (h * 3)/4;
    }
}

int main(){
    //When I tested each variation, i did so by commenting the others out
    srand(time(NULL)); //set seed for rand() function
    const int n = 30;
    int data[n];

    for (int & i : data) {
        i = rand() % 500000;
    }
    cout << "Before sorting: ";
    for (int i : data) {
        cout << i << " ";
    }
    cout << endl;
    auto start = steady_clock::now();
    Shellsort_a(data, n);
    auto end = steady_clock::now();

    cout << "After sorting using a: ";
    for (int i : data) {
        cout << i << " ";
    }
    auto duration = duration_cast<microseconds>(end - start);
    cout << "\nTime for Shellsort_a: " << fixed  << duration.count()/1000.0 << " milliseconds" << endl;

    int data2[n];
    for (int & i : data2) {
        i = rand() % 500000;
    }
    cout << "\nBefore sorting: ";
    for (int i : data2) {
        cout << i << " ";
    }
    auto start2 = steady_clock::now();
    Shellsort_b(data2, n);
    auto end2 = steady_clock::now();

    cout << "\nAfter sorting using b: ";
    for (int i : data2) {
        cout << i << " ";
    }
    auto duration2 = duration_cast<microseconds>(end2 - start2);
    cout << "\nTime for Shellsort_b: " << fixed  << duration2.count()/1000.0 << " milliseconds" << endl;

    int data3[n];
    for (int & i : data3) {
        i = rand() % 500000;
    }
    cout << "\nBefore sorting: ";
    for (int i : data3) {
        cout << i << " ";
    }
    auto start3 = steady_clock::now();
    Shellsort_c(data3, n);
    auto stop3 = steady_clock::now();

    cout << "\nAfter sorting using c: ";
    for (int i : data3) {
        cout << i << " ";
    }
    auto duration3 = duration_cast<microseconds>(stop3 - start3);
    cout << "\nTime for Shellsort_c: " << fixed  << duration3.count()/1000.0 << " milliseconds" << endl;

    int data4[n];
    for (int & i : data4) {
        i = rand() % 500000;
    }
    cout << "\nBefore sorting: ";
    for (int i : data4) {
        cout << i << " ";
    }
    auto start4 = steady_clock::now();
    Shellsort_d(data4, n);
    auto stop4 = steady_clock::now();

    cout << "\nAfter sorting using d: ";
    for (int i : data4) {
        cout << i << " ";
    }
    auto duration4 = duration_cast<microseconds>(stop4 - start4);
    cout << "\nTime for Shellsort_d: " << fixed  << duration4.count()/1000.0 << " milliseconds" << endl;

    int data5[n];
    for (int & i : data5) {
        i = rand() % 500000;
    }
    cout << "\nBefore sorting: ";
    for (int i : data5) {
        cout << i << " ";
    }
    auto start5 = steady_clock::now();
    Shellsort_e(data5, n);
    auto stop5 = steady_clock::now();

    cout << "\nAfter sorting using e: ";
    for (int i : data5) {
        cout << i << " ";
    }
    auto duration5 = duration_cast<microseconds>(stop5 - start5);
    cout << "\nTime for Shellsort_e: " << fixed  << duration5.count()/1000.0 << " milliseconds" << endl;

    return 0;
}