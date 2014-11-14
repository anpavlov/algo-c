/*
 *
 * author: a.pavlov
 * group: АПО-12
 * task: 2_3. Ломаная 2.
 * Аналогично 1.2, но ломаная должна быть замкнутая.
 * Предполагается, что никакие три точки не лежат
 * на одной прямой.
 *
 */

#include <iostream>
#include <assert.h>

//=====CArray=====
template< class T >
class CArray
{
public:
    CArray(int cap = 100);
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


//=====HEAP=====
template< class T >
class Heap
{
public:
    Heap(int cap = 10);
    ~Heap();
    
    T ExtractMin();
    void Insert(T element);
    T PeekAtNext() { return IsEmpty() ? 0 : buffer[0]; }
    
    bool IsEmpty() { return size == 0; }
    int GetSize() { return size; }
    
private:
        
    void SiftDown(int index);
    void SiftUp(int index);
        
    void Reallocate();
    
    T* buffer;
    int size;
    int capacity;
};

//=====POINT=====
class Point
{
public:
    Point();
    Point(int newX, int newY);
    Point(const Point& point);
    
    int getX() const { return x; }
    int getY() const { return y; }
    
    Point& operator=(const Point& point);
    bool operator<(const Point& point);
    bool operator<=(const Point& point);
    bool operator==(const Point& point);
    friend std::istream& operator>>(std::istream& stream, Point& p);
    friend std::ostream& operator<<(std::ostream& stream, Point& p);
    
private:
    int x;
    int y;
};

template< class T >
void inputArray(CArray<T>& arr);

template< class T >
void heapSort(CArray<T>& arr);

//================ MAIN ========================

int main()
{
    CArray<Point> arr;
    inputArray(arr);
    heapSort(arr);
    
    for ( int i = 0; i < arr.GetSize(); ++i )
        std::cout << arr[i] << std::endl;
    
    return 0;
}

//===============================================

template< class T >
void inputArray(CArray<T>& arr)
{
    int n = 0;
    std::cin >> n;
    Point p;
    for ( int i = 0; i < n; ++i )
    {
        std::cin >> p;
        arr.Add(p);
    }
}

template< class T >
void heapSort(CArray<T>& arr)
{
    Heap<T> heap;
    for ( int i = 0; i < arr.GetSize(); ++i )
        heap.Insert(arr[i]);
    for ( int i = 0; i < arr.GetSize(); ++i )
        arr[i] = heap.ExtractMin();
}

template< class T >
Heap<T>::Heap(int cap)
    : size(0)
    , capacity(cap)
{
    buffer = new T[capacity];
}

template< class T >
Heap<T>::~Heap()
{
    delete[] buffer;
}

template< class T >
void Heap<T>::SiftDown(int index)
{
    int leftSon = 2 * index + 1;
    int rightSon = 2 * index + 2;
    
    int smallestSon = index;
    
    if ( leftSon < size && buffer[leftSon] < buffer[index] )
        smallestSon = leftSon;
    
    if ( rightSon < size && buffer[rightSon] < buffer[smallestSon] )
        smallestSon = rightSon;
    
    if ( smallestSon != index )
    {
        std::swap(buffer[index], buffer[smallestSon]);
        SiftDown(smallestSon);
    }    
}

template< class T >
void Heap<T>::SiftUp(int index)
{
    while ( index > 0 )
    {
        int parent = ( index - 1 ) / 2;
        
        if ( buffer[parent] <= buffer[index] )
            return;
        
        std::swap(buffer[index], buffer[parent]);
        
        index = parent;
    }
}

template< class T >
void Heap<T>::Reallocate()
{
    int new_capacity = capacity * 2;
    T* new_buffer = new T[new_capacity];
    
    for ( int i = 0; i < capacity; i++ )
        new_buffer[i] = buffer[i];
    
    delete[] buffer;
    
    buffer = new_buffer;
    capacity = new_capacity;
}

template< class T >
void Heap<T>::Insert(T element)
{
    buffer[size] = element;
    SiftUp(size++);
    
    if ( size == capacity )
        Reallocate();
}

template< class T >
T Heap<T>::ExtractMin()
{
    if ( IsEmpty() )
    {
        T t;
        return t;
    }
    
    T result = buffer[0];
    
    buffer[0] = buffer[size - 1];
    size--;
    SiftDown(0);
    
    return result;
}



Point::Point()
    : x(0)
    , y(0)
{
}

Point::Point(int newX, int newY)
    : x(newX)
    , y(newY)
{
}

Point::Point(const Point& point)
    : x(point.getX())
    , y(point.getY())
{
}

Point& Point::operator=(const Point& point)
{
    x = point.getX();
    y = point.getY();
    return *this;
}

bool Point::operator<(const Point &point)
{
    if ( x == point.getX() )
        return ( y < point.getY() );
    return ( x < point.getX() );
}

bool Point::operator<=(const Point &point)
{
    if ( (*this) < point || (*this) == point )
        return true;
    return false;
}

bool Point::operator==(const Point &point)
{
    return ( x == point.getX() && y == point.getY() );
}

std::istream& operator>>(std::istream& stream, Point& p)
{
    int x = 0, y = 0;
    stream >> x >> y;
    Point newP(x, y);
    p = newP;
    return stream;
}

std::ostream& operator<<(std::ostream& stream, Point& p)
{
    stream << p.getX() << " " << p.getY();
    return stream;
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
