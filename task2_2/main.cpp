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
#include <cmath>
//#include <assert.h>

//=====CArray=====
template< class T >
class CArray
{
public:
    CArray(int cap = 100);
    ~CArray();
    
    // Добавление элемента в конец массива
    void Add(T elem);
    void DeleteAt(int index);
    
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
    int getBX() const { return baseX; }
    int getBY() const { return baseY; }
    void SetBase(int bX, int bY);
    
    Point& operator=(const Point& point);
    bool operator<(const Point& point);
    bool operator<=(const Point& point);
    bool operator==(const Point& point);
    friend std::istream& operator>>(std::istream& stream, Point& p);
    friend std::ostream& operator<<(std::ostream& stream, Point& p);
    
private:
    int x;
    int y;
    int baseX;
    int baseY;
};

template< class T >
void inputArray(CArray<T>& arr);

template< class T >
void heapSort(CArray<T>& arr);

int findFirst(CArray<Point>& arr);

void checkLast(CArray<Point>& arr);

//================ MAIN ========================

int main()
{
    CArray<Point> arr;
    inputArray(arr);
    
    int minPoint = findFirst(arr);
    int minX = arr[minPoint].getX();
    int minY = arr[minPoint].getY();
    arr.DeleteAt(minPoint);
    
    for ( int i = 0; i < arr.GetSize(); ++i )
        arr[i].SetBase(minX, minY);
    
    heapSort(arr);
    
    checkLast(arr);
    
    std::cout << minX << " " << minY << std::endl;
    for ( int i = 0; i < arr.GetSize(); ++i )
        std::cout << arr[i] << std::endl;
    
    return 0;
}

//===============================================

void checkLast(CArray<Point>& arr)
{
    int last = arr.GetSize() - 1;
    int x = arr[last].getX();
    int y = arr[last].getY();
    int x1 = arr[last - 1].getX();
    int y1 = arr[last - 1].getY();
    int baseX = arr[0].getBX();
    int baseY = arr[0].getBY();
    
    if ( (y - baseY)/(x - baseX) == (y1 - baseY)/(x1 - baseX) )
        std::swap(arr[last], arr[last - 1]);
}

int findFirst(CArray<Point>& arr)
{
    int min = 0;
    for ( int i = 1; i < arr.GetSize(); ++i )
    {
        if ( arr[i].getX() < arr[min].getX() )
            min = i;
        else
            if ( arr[i].getX() == arr[min].getX() )
                if ( arr[i].getY() < arr[min].getY() )
                    min = i;
    }
    return min;
}

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
    , baseX(point.getBX())
    , baseY(point.getBY())
{
}

void Point::SetBase(int bX, int bY)
{
    baseX = bX;
    baseY = bY;
}

Point& Point::operator=(const Point& point)
{
    x = point.getX();
    y = point.getY();
    baseX = point.getBX();
    baseY = point.getBY();
    return *this;
}

bool Point::operator<(const Point &point)
{
    /*
    if ( (x - baseX) == 0 )
    {
        if ( (point.getX() - baseX) == 0 )
            return false;
        else
            return true;
    }
    if ( (point.getX() - baseX) == 0 )
        return false;
    //int tg1 = (y - baseY)/(x - baseX);
    */
    if ( atan2((y - baseY), (x - baseX)) > atan2((point.getY() - baseY), (point.getX() - baseX)) )
        return true;
    else
        if ( atan2((y - baseY), (x - baseX)) == atan2((point.getY() - baseY), (point.getX() - baseX)) )
        {
            double dist1 = (y - baseY)*(y - baseY) - (x - baseX)*(x - baseX);
            double dist2 = (point.getY() - baseY)*(point.getY() - baseY) - (point.getX() - baseX)*(point.getX() - baseX);
            return dist1 < dist2;
        }
    return false;
}

bool Point::operator<=(const Point &point)
{
    if ( (*this) < point || (*this) == point )
        return true;
    return false;
}

bool Point::operator==(const Point &point)
{
    if ( (x - baseX) == 0 )
    {
        if ( (point.getX() - baseX) == 0 )
            return true;
        else
            return false;
    }
    if ( (point.getX() - baseX) == 0 )
    {
        if ( (x - baseX) == 0 )
            return true;
        else
            return false;
    }
    bool is = (y - baseY)/(x - baseX) == (point.getY() - baseY)/(point.getX() - baseX);
    return is;
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
