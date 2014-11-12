/*
 *
 * author: a.pavlov
 * group: АПО-12
 * task: 4_2. Реализовать дек с динамическим буфером.
 * 
 * В первой строке количество команд.
 * Каждая команда задаётся как 2 целых числа: a b.
 * a = 1 - push front
 * a = 2 - pop front
 * a = 3 - push back
 * a = 4 - pop back
 * Для очереди используются команды 2 и 3.
 * Для дека используются все четыре команды.
 * Если дана команда pop*, то число b - ожидаемое
 * значение. Если команда pop вызвана для пустой
 * структуры данных, то ожидается “-1
 *
 */

#include <iostream>

void pr(int* arr, int n)
{
    for(int i = 0; i<n;i++)
        std::cout<<arr[i]<<' ';
    std::cout<<std::endl;
}

// Дек через динамический буфер
class Deque
{
public:
    Deque(int cap = 50 );
    ~Deque();
    
    void PushBack(int in);
    void PushFront(int in);
    
    int PopBack();
    int PopFront();
    
    // Длина дека
    int Length() { return size; }
    
    // Проверка на пустоту
    bool IsEmpty() { return ( size == 0 ); }
    
private:
    
    // Добавление свободных ячеек
    void ReAllocate();
    
    // Буфер
    int* buffer;
    
    // Доступный размер
    int capacity;
    
    // Количество элементов
    int size;
    
    // Индекс ячейки перед первым элементом
    int first;
    
    // Индекс последнего элемента
    int last;
};

Deque::Deque(int cap)
{
    capacity = cap;
    buffer = new int[capacity];
    first = capacity / 2;
    last = first;
    size = 0;
}

Deque::~Deque()
{
    delete[] buffer;
}

void Deque::PushBack(int in)
{
    if ( size != 0 && first == last )
        ReAllocate();
    if ( last + 1 == capacity )
        last = 0;
    else
        last++;
    buffer[last] = in;
    size++;
    
    //pr(buffer, capacity);
}

void Deque::PushFront(int in)
{
    if ( size != 0 && first == last )
        ReAllocate();
    buffer[first--] = in;
    if ( first < 0 )
        first = capacity - 1;
    size++;
    
    //pr(buffer, capacity);
}

int Deque::PopBack()
{
    size--;
    int temp = buffer[last];
    buffer[last] = 0;
    if ( last == 0 )
        last = capacity - 1;
    else
        last--;
    
    //pr(buffer, capacity);
    return temp;
}

int Deque::PopFront()
{
    size--;
    
    if ( first == capacity - 1)
        first = 0;
    else
        first++;
    int t = buffer[first];
    buffer[first] = 0;
    
    //pr(buffer, capacity);
    
    return t;//buffer[first];
}

void Deque::ReAllocate()
{    
    int new_capacity = capacity * 2;
    int* new_buffer = new int[new_capacity];
    
    for ( int i = 0; i <= last; i++ )
        new_buffer[i] = buffer[i];
    
    first = new_capacity - capacity + last;
    
    if ( last + 1 < capacity )
        for ( int i = last + 1; i < capacity; i++ )
            new_buffer[first + i - last] = buffer[i];
        
    
    
    delete[] buffer;
    
    buffer = new_buffer;
    capacity = new_capacity;
}

// Возвращает соответствие возвращаемого элемента ожидаемому
bool CheckPopBack(Deque* D, int expected)
{
    bool Empty = D->IsEmpty();
    if ( Empty )
        return ( Empty && ( expected == -1 ) );
    return ( D->PopBack() == expected );
}

// Возвращает соответствие возвращаемого элемента ожидаемому
bool CheckPopFront(Deque* D, int expected)
{
    bool Empty = D->IsEmpty();
    if ( Empty )
        return ( Empty && ( expected == -1 ) );
    return ( D->PopFront() == expected );
}


// Основные вычисления
bool inputLoop(int n)
{
    Deque D(4);
    int a = 0, b = 0;
    bool canDo = true;
    
    for ( int i = 0; i < n; i++)
    {
        std::cin >> a >> b;
        switch (a)
        {
        case 1:
            D.PushFront(b);
            break;
        case 2:
            canDo = canDo && CheckPopFront(&D, b);
            break;
        case 3:
            D.PushBack(b);
            break;
        case 4:
            canDo = canDo && CheckPopBack(&D, b);
            break;
        }
    }
    
    return canDo;
}

int main()
{
    int n = 0;
    
    // Ввод n
    std::cin >> n;
    
    if ( inputLoop(n) )
        std::cout << "YES";
    else
        std::cout << "NO";
    return 0;
}

