/*
 *
 * author: a.pavlov
 * group: АПО-12
 * task: 2_1. Даны два массива целых чисел одинаковой длины A[0..n-1] и B[0..n-1].
 * Необходимо найти первую пару индексов i0 и j0, i0 <= j0,
 * такую что A[i0] + B[j0] = max {A[i] + B[j],
 * где 0 <= i < n, 0 <= j < n, i <= j}. Время работы - O(n).
 *
 */

#include <iostream>

// Ввод целочисленного массива
void intArrayInput(int* arr, int n) {
    for( int i = 0; i < n; i++ ) {
        std::cin >> arr[i];
    }
}

// Нахождение i0 и j0
void findi0j0(int* A, int* B, int n, int& i0, int& j0) {
    int imax = 0, maxSum = A[0] + B[0], tmpSum = 0;

    for( int i = 0; i < n; i++ ) {
        if ( A[i] > A[imax] ) {
            imax = i;
        }
        tmpSum = A[imax] + B[i];
        if ( tmpSum > maxSum ) {
            maxSum = tmpSum;
            i0 = imax;
            j0 = i;
        }
    }
}

int main()
{
    int n = 0;

    // Ввод n
    std::cin >> n;

    int *A = new int[n];

    // Ввод первого массива
    intArrayInput(A, n);

    int *B = new int[n];

    // Ввод второго массива
    intArrayInput(B, n);

    int i0 = 0, j0 = 0;

    findi0j0(A, B, n, i0, j0);

    std::cout << i0 << " " << j0;

    delete [] A;
    delete [] B;

    return 0;
}

