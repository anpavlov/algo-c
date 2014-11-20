/*
 *
 * author: a.pavlov
 * group: АПО-12
 * task: 5_3. Количество инверсий
 * Дана последовательность целых чисел из
 * диапазона (-10^9 .. 10^9). Длина
 * последовательности не больше 10^6. Числа
 * записа по одному в строке. Количество
 * чисел не указано. Пусть количество
 * элементов n, и числа записаны в
 * массиве a = a[i]:i из [0..n-1]. Требуется
 * напечатать количество таких пар
 * индексов (i,j) из [0..n-1],
 * что (i < j и a[i], > a[j]);
 *
 */

#include <cstdio>
#include <stdint.h>

template< class T >
class CArray
{
public:
    CArray(int cap = 100);
    CArray(CArray<T>& arr, int start, int end);
    ~CArray();
    
    // Добавление элемента в конец массива
    void Add(T elem);
    void DeleteAt(int index);
    
    // Оператор индексации
    T& operator [](int index);
    
    // Получение размера массива
    int GetSize() { return size; }
    int GetCapacity() { return capacity; }
    
private:
    
    // Расширение массива
    void Reallocate();
    
    T* buffer;
    int capacity;
    int size;
};

void inputIntArray(CArray<int>& arr);

template< class T >
int64_t mergeSort(CArray<T>& arr);

template< class T >
int64_t splitAndMerge(CArray<T>& arr, int start, int end, CArray<T>& buffer);

int main()
{
    CArray<int> arr;
    inputIntArray(arr);
    
    int64_t inv = mergeSort(arr);
    printf("%ld", inv);
    return 0;
}

void inputIntArray(CArray<int>& arr)
{
    int temp;
    while ( scanf("%d", &temp) == 1 )
        arr.Add(temp);
}

template< class T >
int64_t mergeSort(CArray<T>& arr)
{
    CArray<T> buf(arr.GetSize());
    int64_t inv = splitAndMerge(arr, 0, arr.GetSize() - 1, buf);
    return inv;
}

template< class T >
int64_t splitAndMerge(CArray<T>& arr, int start, int end, CArray<T>& buffer)
{
    if ( end - start == 0 )
        return 0;
    
    //CArray<T> half1(arr, , arr.GetSize() / 2 - 1);
    //CArray<T> half2(arr, arr.GetSize() / 2, arr.GetSize() - 1);
    
    int half1_end = (end - start) / 2 + start;
    int half2_start = half1_end + 1;
    int64_t inv1 = splitAndMerge(arr, start, half1_end, buffer);
    int64_t inv2 = splitAndMerge(arr, half2_start, end, buffer);
    
    int64_t inv3 = 0;
    int j = start;
    int k = half2_start;
    for ( int i = start; i <= end; ++i )
    {
        if ( j <= half1_end && k <= end )
        {
            if ( arr[j] <= arr[k] )
            {
                buffer[i] = arr[j];
                ++j;
            }
            else
            {
                inv3 += (half1_end - j + 1);
                buffer[i] = arr[k];
                ++k;
            }
        }
        else
        {
            if ( j <= half1_end )
            {
                buffer[i] = arr[j];
                ++j;
            }
            else
            {
                buffer[i] = arr[k];
                ++k;
            }
        }
    }
    
    for ( int i = start; i <= end; ++i )
    {
        arr[i] = buffer[i];
    }
    
    return inv1 + inv2 + inv3;
}

template< class T >
CArray<T>::CArray(int cap)
    : capacity(cap)
    , size(0)
{
    buffer = new T[capacity];
}

template< class T >
CArray<T>::CArray(CArray<T> &arr, int start, int end)
    : capacity(arr.GetCapacity())
    , size(0)
{
    buffer = new T[capacity];
    int last = arr.GetSize() - 1;
    if ( start < 0 )
        start = 0;
    else
        if ( start > last )
            start = last;
    if ( end > last)
        end = last;
    else
        if ( end < 0 )
            end = 0;
    for ( int i = start; i < end + 1; ++i )
        Add(arr[i]);
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
void CArray<T>::DeleteAt(int index)
{
    if ( index < 0 )
        return;
    for ( int i = index; i < size - 1; ++i )
        buffer[i] = buffer[i + 1];
    --size;
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
    //assert(index >= 0 && index < size);
    return buffer[index];
}
