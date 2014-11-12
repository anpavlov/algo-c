/*
 *
 * author: a.pavlov
 * group: АПО-12
 * task: 1_3. Сортировка пузырьком.
 *
 */

#include <iostream>
#include <cstdio>
#include <assert.h>
#include <ctime>

// Динамический массив
template< class T >
class CArray
{
public:
    CArray(int cap = 1000);
    ~CArray();
    
    // Добавление элемента в конец массива
    void Add(T elem);
    
    // Оператор индексации
    T& operator [](int index);
    
    // Получение размера массива
    int GetSize() { return size; }
    
private:
    
    // Расширение массива
    void Reallocate();
    
    T* buffer;
    int capacity;
    int size;
};

// Ввод целочисленного массива
void inputIntArray(CArray<int>& arr);

// Сортировка пузырьком
template< class T >
void bubbleSort(CArray<T>& arr);

// Вывод массива
template< class T >
void outputArray(CArray<T>& arr);

//============= MAIN =========================

int main()
{
    CArray<int> arr;
    inputIntArray(arr);
    clock_t t1 = clock();
    
    bubbleSort(arr);
    outputArray(arr);
    clock_t t2 = clock();
    
    std::cout << '\n' << ((float)(t2 - t1))/CLOCKS_PER_SEC/1000;
    
    return 0;
}

//============================================

// Ввод массива
void inputIntArray(CArray<int>& arr)
{
    int temp;
    while ( scanf("%d", &temp) == 1 )
        arr.Add(temp);
}

// Сортировка
template< class T >
void bubbleSort(CArray<T>& arr)
{
    int swaps = 0;
    for ( int i = 0; i < arr.GetSize() - 1; ++i )
    {
        swaps = 0;
        for ( int j = 0; j < arr.GetSize() - i - 1; ++j )
            if ( arr[j] > arr[j + 1] )
            {
                std::swap(arr[j], arr[j + 1]);
                ++swaps;
            }
        if ( swaps == 0)
            break;
    }
}

// Вывод массива
template< class T >
void outputArray(CArray<T>& arr)
{
    int i = 0;
    for ( i = 0; i < arr.GetSize() - 1; ++i )
        std::cout << arr[i] << std::endl;
    std::cout << arr[i];
}

template< class T >
CArray<T>::CArray(int cap)
    : capacity(cap)
    , size(0)
{
    buffer = new T[capacity];
}

template<class T>
CArray<T>::~CArray()
{
    delete[] buffer;
}

template<class T>
void CArray<T>::Add(T elem)
{
    if ( size == capacity )
        Reallocate();
    buffer[size++] = elem;
}

template<class T>
void CArray<T>::Reallocate()
{
    int new_capacity = capacity * 2;
    T* new_buffer = new T[new_capacity];
    
    for ( int i = 0; i < capacity; i++ )
        new_buffer[i] = buffer[i];
    
    delete[] buffer;
    
    buffer = new_buffer;
    capacity = new_capacity;
}

template<class T>
T& CArray<T>::operator [](int index)
{
    assert(index >= 0 && index < size);
    return buffer[index];
}
