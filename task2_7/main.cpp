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
void qs(CArray<T>& arr, int first, int last);

template< class T >
void optiSort(CArray<T>& arr);

template< class T >
int partition(CArray<T>& arr, int start, int end, int pivot);

void inputIntArray(CArray<int>& arr);

int main()
{
    CArray<int> arr(26000000);
    inputIntArray(arr);
    
    qs(arr, 0, arr.GetSize() - 1);
    
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
    
    int start = 0;
    int last = arr.GetSize() - 1;
    stack.Push(start);
    stack.Push(last);
    int p = 0;
    
    while ( !(stack.IsEmpty()) )
    {
        last = stack.Pop();
        start = stack.Pop();
        
        p = partition(arr, first, last, 0);
     
        if ( p < last )
            qs(arr, p + 1, last);
        if (first < p - 1)
            qs(arr, first, p - 1);
    }
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
    char* new_buffer = new T[new_capacity];
    
    for ( int i = 0; i < capacity; i++ )
        new_buffer[i] = buffer[i];
    
    delete[] buffer;
    
    buffer = new_buffer;
    capacity = new_capacity;
}
