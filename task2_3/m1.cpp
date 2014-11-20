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

template< class T >
void splitAndMerge(CArray<T>& arr, int start, int end, CArray<T>& buffer);

void input(CArray<Point>& arr);

int countOneThicknessLength(CArray<Point>& arr);

int main()
{
    CArray<Point> arr;
    
    input(arr);
    
    mergeSort(arr);
    
    int length = countOneThicknessLength(arr);
    
    std::cout << length;
    
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

void input(CArray<Point>& arr)
{
    int n = 0;
    std::cin >> n;
    int start = 0, finish = 0;
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
    CArray<T> buf(arr.GetSize());
    splitAndMerge(arr, 0, arr.GetSize() - 1, buf);
}

template< class T >
void splitAndMerge(CArray<T>& arr, int start, int end, CArray<T>& buffer)
{
    if ( end - start == 0 )
        return;
    
    //CArray<T> half1(arr, , arr.GetSize() / 2 - 1);
    //CArray<T> half2(arr, arr.GetSize() / 2, arr.GetSize() - 1);
    
    int half1_end = (end - start) / 2 + start;
    int half2_start = half1_end + 1;
    splitAndMerge(arr, start, half1_end, buffer);
    splitAndMerge(arr, half2_start, end, buffer);
    
    int j = start, k = half2_start;
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

