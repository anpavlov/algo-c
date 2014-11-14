
/*
 *
 * author: a.pavlov
 * group: АПО-12
 * task: 1_3. Сортировка пузырьком.
 *
 */

#include <iostream>
#include <cstdio>

int inputIntArray(int*& arr, int n)
{
    int temp, i = 0;
    while ( scanf("%d", &temp) == 1 )
    {
        if ( i == n)
        {
            int new_n = n * 2;
            int* new_arr = new int[new_n];
            
            for ( int j = 0; j < n; j++ )
                std::swap(new_arr[j],arr[j]);
            
            delete[] arr;
            
            arr = new_arr;
            n = new_n;
        }
        std::swap(arr[i++],temp);
    }
    return i;
}

// Сортировка
void bubbleSort(int* arr, int n)
{
    int swaps = 0;
    for ( int i = 0; i < n - 1; ++i )
    {
        swaps = 0;
        for ( int j = 0; j < n - i - 1; ++j )
            if ( arr[j] > arr[j + 1] )
            {
                std::swap(arr[j], arr[j + 1]);
                swaps = 1;
            }
        if ( swaps == 0)
            break;
    }
}

// Вывод массива
void outputArray(int* arr, int n)
{
    int i = 0;
    for ( i = 0; i < n - 1; ++i )
        std::cout << arr[i] << std::endl;
    std::cout << arr[n - 1];
}

int main() {
    
    int n = 100;
    int* arr= new int[n];
    int m = inputIntArray(arr,n);
    
    bubbleSort(arr, m);
    outputArray(arr,m);
    
    return 0;
}

