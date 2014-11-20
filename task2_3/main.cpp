/*
 *
 * author: a.pavlov
 * group: АПО-12
 * task: 3_4. Закраска прямой 2.
 * На числовой прямой окрасили N отрезков.
 * Известны координаты левого и правого концов
 * каждого отрезка (Li и Ri). Найти сумму длин
 * частей числовой прямой, окрашенных ровно
 * в один слой.
 *
 */

#include <iostream>

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

enum PointType { START, FINISH };

struct Point {
    Point() {}
    Point(int nX, PointType t) : x(nX), type(t) {}
    int x;
    PointType type;
};

bool operator<= (Point& point1, Point& point2);

template< class T >
void mergeSort(CArray<T>& arr);

void input(CArray<Point>& arr);

int countOneThicknessLength(CArray<Point>& arr);

int abc()
{
    CArray<Point> arr;
    
    input(arr);
    
    mergeSort(arr);
    
    int length = countOneThicknessLength(arr);
    
    std::cout<<length;
    
    return 0;
}

int countOneThicknessLength(CArray<Point>& arr)
{
    bool isOne = false;
    int thickness = 0;
    int oneBegin = 0;
    int length = 0;
    for ( int i = 0; i < arr.GetSize(); ++i )
    {
        if ( arr[i].type == START )
            ++thickness;
        else
            --thickness;
        if ( thickness != 1 )
        {
            if ( isOne == true )
            {
                isOne = false;
                length += (arr[i].x - oneBegin);
            }
        }
        else
        {
            if ( isOne == false )
            {
                isOne = true;
                oneBegin = arr[i].x;
            }
        }
    }
    return length;
}

bool operator<= (Point& point1, Point& point2)
{
    return point1.x <= point2.x;
}

void input(Point*& arr)
{
    int n;
    std::cin >> n;
    int start, finish;
    for ( int i = 0; i < n; ++i )
    {
        std::cin >> start >> finish;
        Point startPoint(start, START);
        Point finishPoint(finish, FINISH);
        arr.Add(startPoint);
        arr.Add(finishPoint);
    }
}

template< class T >
void mergeSort(CArray<T>& arr)
{
    if ( arr.GetSize() == 1 )
        return;
    
    CArray<T> half1(arr, 0, arr.GetSize() / 2 - 1);
    CArray<T> half2(arr, arr.GetSize() / 2, arr.GetSize() - 1);
    
    mergeSort(half1);
    mergeSort(half2);
    
    int j = 0, k = 0;
    for ( int i = 0; i < arr.GetSize(); ++i )
    {
        if ( j < half1.GetSize() && k < half2.GetSize() )
        {
            if ( half1[j] <= half2[k] )
            {
                arr[i] = half1[j];
                ++j;
            }
            else
            {
                arr[i] = half2[k];
                ++k;
            }
        }
        else
        {
            if ( j < half1.GetSize() )
            {
                arr[i] = half1[j];
                ++j;
            }
            else
            {
                arr[i] = half2[k];
                ++k;
            }
        }
    }
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
