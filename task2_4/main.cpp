/*
 *
 * author: a.pavlov
 * group: АПО-12
 * task: 4_3. Реализуйте стратегию выбора
 * опорного элемента “случайный элемент”.
 * Функцию Partition реализуйте методом
 * прохода двумя итераторами от начала
 * массива к концу.
 *
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

int partition(int*& arr, int start, int end);

int input(int*& arr, int& n);

int findkElem(int*& arr, int n, int k);

int main()
{
    int* arr;
    int n = 0;
    int k = input(arr, n);
    std::cout << findkElem(arr, n, k);
    
    return 0;
}

int input(int*& arr, int &n)
{
    int k;
    std::cin >> n >> k;
    arr = new int[n];
    for ( int i = 0; i < n; ++i )
        std::cin >> arr[i];
    return k;
}

int findkElem(int*& arr, int n, int k)
{
    int start = 0, end = n - 1, p = -1;
    while ( p != k )
    {
        p = partition(arr, start, end);
        if ( k > p )
            start = p + 1;
        if ( k < p )
            end = p - 1;
    }
    return arr[k];
}

int partition(int*& arr, int start, int end)
{
    if ( start == end )
        return start;
    
    srand(time(NULL));
    
    int pivot = rand() % (end - start + 1) + start;
    std::swap(arr[pivot], arr[end]);
    pivot = end;
    int i = start;
    int j = i;
    while ( j < end )
    {
        if ( arr[j] <= arr[pivot] )
        {
            std::swap(arr[j], arr[i]);
            ++i;
            ++j;
        }
        while ( arr[j] > arr[pivot] ) ++j;
    }
    std::swap(arr[i], arr[pivot]);
    pivot = i;
    return pivot;
}
