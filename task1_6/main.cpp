/*
 *
 * author: a.pavlov
 * group: АПО-12
 * task: 6_3. Тупики.
 * На вокзале есть некоторое количество тупиков,
 * куда прибывают электрички. Этот вокзал является
 * их конечной станцией. Дано расписание движения
 * электричек, в котором для каждой электрички
 * указано время ее прибытия, а также время
 * отправления в следующий рейс. Электрички в
 * расписании упорядочены по времени прибытия.
 * Когда электричка прибывает, ее ставят в
 * свободный тупик с минимальным номером. При
 * этом если электричка из какого-то тупика
 * отправилась в момент времени X, то электричку,
 * которая прибывает в момент времени X, в этот тупик
 * ставить нельзя, а электричку, прибывающую в
 * момент X+1 — можно.
 * В данный момент на вокзале достаточное количество
 * тупиков для работы по расписанию. Напишите программу,
 * которая по данному расписанию определяет, какое
 * минимальное количество тупиков требуется для работы вокзала.
 * 
 * Формат входных данных.
 * Вначале вводится n - количество электричек в расписании.
 * Затем вводится n строк для каждой электрички, в строке -
 * время прибытия и время отправления. Время - натуральное
 * число от 0 до 10^9. Строки в расписании упорядочены по
 * времени прибытия.
 * 
 * Формат выходных данных.
 * Натуральное число - минимальное количеством тупиков.
 *
 */

#include <iostream>

class Heap
{
public:
    Heap(int cap = 10);
    ~Heap();
    
    int ExtractMin();
    void Insert(int element);
    int PeekAtNext() { return IsEmpty() ? 0 : buffer[0]; }
    
    bool IsEmpty() { return size == 0; }
    int GetSize() { return size; }
    
private:
        
    void SiftDown(int index);
    void SiftUp(int index);
        
    void Reallocate();
    
    int* buffer;
    int size;
    int capacity;
};

// Подсчет минимально необходимого количества тупиков
int CountDeadlocks(int n);

int main()
{
    int n = 0;
    
    // Ввод n
    std::cin >> n;
    
    int minDeadlocks = CountDeadlocks(n);
    
    std::cout << minDeadlocks;
    
    return 0;
}

Heap::Heap(int cap)
{
    capacity = cap;
    size = 0;
    buffer = new int[capacity];
}

Heap::~Heap()
{
    delete[] buffer;
}

void Heap::SiftDown(int index)
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

void Heap::SiftUp(int index)
{
    while ( index > 0 )
    {
        int parent = ( index - 1 ) / 2;
        
        if ( buffer[index] >= buffer[parent] )
            return;
        
        std::swap(buffer[index], buffer[parent]);
        
        index = parent;
    }
}

void Heap::Reallocate()
{
    int new_capacity = capacity * 2;
    int* new_buffer = new int[new_capacity];
    
    for ( int i = 0; i < capacity; i++ )
        new_buffer[i] = buffer[i];
    
    delete[] buffer;
    
    buffer = new_buffer;
    capacity = new_capacity;
}

void Heap::Insert(int element)
{
    buffer[size] = element;
    SiftUp(size++);
    
    if ( size == capacity )
        Reallocate();
}

int Heap::ExtractMin()
{
    if ( IsEmpty() )
        return 0;
    
    int result = buffer[0];
    
    buffer[0] = buffer[size - 1];
    size--;
    SiftDown(0);
    
    return result;
}

// Подсчет минимально необходимого количества тупиков
int CountDeadlocks(int n)
{
    int minDeadlocks = 0;
    int arrival = 0, departure = 0;
    Heap heap;
    
    for ( int i = 0; i < n; i++ )
    {
        // Ввод времени прибытия и отбытия
        std::cin >> arrival >> departure;
        
        if ( !heap.IsEmpty() )
        {
            // Если некоторые электрички к моменту прибытия уехали - извлекаем
            while ( arrival > heap.PeekAtNext() )
                heap.ExtractMin();
        }
        
        // Добавляем время отправления прибывшей
        heap.Insert(departure);
        
        // Смотрим, сколько путей занято
        if ( heap.GetSize() > minDeadlocks )
            minDeadlocks = heap.GetSize();
    }
    
    return minDeadlocks;
}


