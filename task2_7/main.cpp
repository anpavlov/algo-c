#include <cstdio>

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

template< class T >
class Stack
{
public:
    Stack(int cap = 1000);
    ~Stack();
    
    void Push(T c);
    T Pop() { size--; return buffer[end--]; }
    
    // Посмотреть последний элемент
    T SeeLast() { return (IsEmpty()) ? 0 : buffer[end]; }
    
    // Проверка на пустоту
    bool IsEmpty() { return size == 0; }
    
    // Узнать размер
    int GetSize() { return size; }
    
private:
    // Переразметка памяти при переполнении буфера
    void ReAllocate();
    
    T* buffer;
    
    int capacity;
    int size;
    int end;
};

template< class T >
void optiSort(CArray<T>& arr);

template< class T >
int partition(CArray<T>& arr, int start, int end, int pivot);

template< class T >
int findMedian(CArray<T>& arr, int start, int end, int step);

template< class T >
void bubbleSort(CArray<T>& arr, int start, int last, int step = 1);

void inputIntArray(CArray<int>& arr);

int main()
{
    CArray<int> arr(25000000);
    inputIntArray(arr);
    
    optiSort(arr);
    //bubbleSort(arr, 0, arr.GetSize() - 1, 2);
    
    for (int i = 9; i < arr.GetSize(); i += 10)
    //for (int i = 0; i < arr.GetSize(); i++)
        printf("%d\n",arr[i]);
    return 0;
}

void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

template< class T >
void optiSort(CArray<T>& arr)
{
    Stack<int> stack;
    
    int first = 0;
    int last = arr.GetSize() - 1;
    stack.Push(first);
    stack.Push(last);
    int p = 0;
    
    while ( !(stack.IsEmpty()) )
    {
        last = stack.Pop();
        first = stack.Pop();
        
        p = findMedian(arr, first, last);
        p = partition(arr, first, last, p);
     
        if ( p < last )
        {
            stack.Push(p + 1);
            stack.Push(last);
        }
        if (first < p - 1)
        {
            stack.Push(first);
            stack.Push(p - 1);
        }
    }
}

template< class T >
int findMedian(CArray<T>& arr, int start, int end)
{
    int first = start;
    int last = end;
    int step = 1;
    
    while ( 1 )
    {
        
        for ( int i = first; i + 4 * step <= last; i += 5 * step )
            bubbleSort(arr, i, i + 4 * step, step);
        
        if ( (last - first)/step + 1 <= 5 )
            break;
        
        first += 2 * step;
        last -= 2 * step;
        step *= 5;
        
    }
    
    int ret = first + step * 2;
    return ret;
}

inline void inputIntArray(CArray<int>& arr)
{
    int temp;
    while ( scanf("%d", &temp) == 1 )
        arr.Add(temp);
}

template< class T >
inline int partition(CArray<T>& arr, int start, int end, int pivot)
{
    if ( pivot < start )
        pivot = start;
    if ( pivot > end )
        pivot = end;
    
    if ( start == end )
        return pivot;

    swap(arr[pivot], arr[end]);
    pivot = end;
    int i = start;
    int j = i;
    while ( j < end )
    {
        if ( arr[j] <= arr[pivot] )
        {
            if ( i != j )
                swap(arr[j], arr[i]);
            ++i;
            ++j;
        }
        while ( arr[j] > arr[pivot] ) ++j;
    }
    swap(arr[i], arr[pivot]);
    pivot = i;
    return pivot;
}

template< class T >
void bubbleSort(CArray<T>& arr, int start, int last, int step)
{
    //int swaps = 0;
    for ( int i = start; i < last; i += step )
    {
        //swaps = 0;
        for ( int j = start; j < last - i; j += step )
            if ( arr[j] > arr[j + step] )
            {
                swap(arr[j], arr[j + step]);
                //swaps = 1;
            }
        //if ( swaps == 0)
            //break;
    }
}

// ======= CArray ==========

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

// ======= Stack =========

template< class T >
Stack<T>::Stack(int cap)
{
    capacity = cap;
    size = 0;
    end = -1;
    buffer = new T[capacity];
}

template< class T >
Stack<T>::~Stack()
{
    delete[] buffer;
}

template< class T >
void Stack<T>::Push(T c)
{
    if ( end == capacity - 1 )
        ReAllocate();
    buffer[++end] = c;
    size++;
}

template< class T >
void Stack<T>::ReAllocate()
{
    int new_capacity = capacity * 2;
    T* new_buffer = new T[new_capacity];
    
    for ( int i = 0; i < capacity; i++ )
        new_buffer[i] = buffer[i];
    
    delete[] buffer;
    
    buffer = new_buffer;
    capacity = new_capacity;
}
