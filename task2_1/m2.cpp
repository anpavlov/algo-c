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

// Динамический массив
class CArray
{
public:
    CArray(int cap = 100);
    ~CArray();
    
    // Добавление элемента в конец массива
    void Add(int elem);
    
    // Оператор индексации
    int& operator [](int index);
    
    // Получение размера массива
    int GetSize() { return size; }
    
private:
    
    // Расширение массива
    void Reallocate();
    
    int* buffer;
    int capacity;
    int size;
};

// Ввод целочисленного массива
void inputIntArray(CArray& arr);

// Сортировка пузырьком
void bubbleSort(CArray& arr);

// Вывод массива
void outputArray(CArray& arr);

//============= MAIN =========================

int adf()
{
    CArray arr;
    inputIntArray(arr);
    
    bubbleSort(arr);
    outputArray(arr);
    
    return 0;
}

//============================================

// Ввод массива
void inputIntArray(CArray& arr)
{
    int temp;
    while ( scanf("%d", &temp) == 1 )
        arr.Add(temp);
}

// Сортировка
void bubbleSort(CArray& arr)
{
    int swaps = 0;
    for ( int i = 0; i < arr.GetSize() - 1; ++i )
    {
        swaps = 0;
        for ( int j = 0; j < arr.GetSize() - i - 1; ++j )
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
void outputArray(CArray& arr)
{
    int i = 0;
    for ( i = 0; i < arr.GetSize() - 1; ++i )
        std::cout << arr[i] << std::endl;
    std::cout << arr[i];
}

CArray::CArray(int cap)
    : capacity(cap)
    , size(0)
{
    buffer = new int[capacity];
}

CArray::~CArray()
{
    delete[] buffer;
}

void CArray::Add(int elem)
{
    if ( size == capacity )
        Reallocate();
    buffer[size++] = elem;
}

void CArray::Reallocate()
{
    int new_capacity = capacity * 2;
    int* new_buffer = new int[new_capacity];
    
    for ( int i = 0; i < capacity; i++ )
        new_buffer[i] = buffer[i];
    
    delete[] buffer;
    
    buffer = new_buffer;
    capacity = new_capacity;
}

int& CArray::operator [](int index)
{
    assert(index >= 0 && index < size);
    return buffer[index];
}
