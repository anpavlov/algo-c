/*
 *
 * author: a.pavlov
 * group: АПО-12
 * task: 6_1. MSD для строк
 * Дан массив строк. Количество
 * строк не больше 105. Отсортировать
 * массив методом поразрядной
 * сортировки MSD по символам.
 * Размер алфавита - 256 символов.
 * Последний символ строки = ‘\0’.
 *
 */

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

void inputStrArray(CArray<char*>& arr);

void MSDstringSort(CArray<char*>& arr);
void charSort(CArray<char*>& arr, int nbyte, int start, int end);

void outputArr(CArray<char*>& arr);

int main()
{
    CArray<char*> arr;
    inputStrArray(arr);
    MSDstringSort(arr);
    outputArr(arr);
    return 0;
}

void charSort(CArray<char*>& arr, int nbyte, int start, int end)
{
    if ( end - start == 0 )
        return;
    
    char minValue = arr[start][nbyte];
	char maxValue = arr[start][nbyte];
    
	for( int i = start; i <= end; ++i ) {
		if ( arr[i][nbyte] < minValue ) minValue = arr[i][nbyte];
		if ( arr[i][nbyte] > maxValue ) maxValue = arr[i][nbyte];
	}
    if ( minValue == 0 && maxValue == 0 )
        return;
    if ( minValue == 0 )
        minValue = 'a' - 1;
	int valuesCount = maxValue - minValue + 1;
	int* valuesData = new int[valuesCount];
	for( int i = 0; i < valuesCount; i++ ) {
		valuesData[i] = 0;
	}

	for( int i = start; i <= end; ++i ) {
        int ind = 0;
        if ( arr[i][nbyte] != 0 )
            ind = arr[i][nbyte] - minValue;
		valuesData[ind]++;
	}

    int* valuesData_t = new int[valuesCount];
    valuesData_t[0] = valuesData[0];

	for( int i = 1; i < valuesCount; ++i ) {
		valuesData[i] += valuesData[i - 1];
        valuesData_t[i] = valuesData[i];
	}

	char** tempData = new char*[end - start + 1];

	for( int i = end; i >= start; --i ) {
        int value = 0;
        if ( arr[i][nbyte] != 0 )
            value = arr[i][nbyte] - minValue;
		valuesData[value]--;
        int ind = valuesData[value];
		tempData[ind] = arr[i];
	}

	for( int i = start, j = 0; i <= end; ++i, ++j ) {
		arr[i] = tempData[j];
	}
    
    int new_start = start;
    int new_end = start + valuesData_t[0] - 1;
    for ( int i = 0; i < valuesCount - 1; ++i )
    {
        charSort(arr, nbyte + 1, new_start, new_end);
        new_start = new_end + 1;
        while ( valuesData_t[i + 1] == valuesData_t[i] )
            ++i;
        new_end = start + valuesData_t[i + 1] - 1;
    }
    if ( valuesCount > 1 )
    {
        charSort(arr, nbyte + 1, new_start, new_end);
    }
    else
        charSort(arr, nbyte + 1, new_start, new_end);

	delete [] tempData;
	delete [] valuesData;
}

void MSDstringSort(CArray<char*>& arr)
{
    charSort(arr, 0, 0, arr.GetSize() - 1);
}

void outputArr(CArray<char*>& arr)
{
    for ( int i = 0; i < arr.GetSize(); ++i )
        printf("%s\n", arr[i]);
}

void inputStrArray(CArray<char*>& arr)
{
    int size = 300;
    char* temp = new char[size];
    while ( scanf("%s", temp) == 1 )
    {
        arr.Add(temp);
        temp = new char[size];
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
