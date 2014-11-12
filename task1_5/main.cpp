/*
 *
 * author: a.pavlov
 * group: АПО-12
 * task: 5_1. Скобочная последовательность.
 * Дан фрагмент последовательности скобок,
 * состоящей из символов (){}[]. Требуется
 * определить, возможно ли продолжить
 * фрагмент в обе стороны, получив корректную
 * последовательность.
 * Формат входных данных.
 * Строка, содержащая символы (){}[] и, возможно,
 * перевод строки. Максимальная длина строки 10^6 символов.
 * Формат выходных данных.
 * Если возможно - вывести минимальную корректную
 * последовательность, иначе - напечатать "IMPOSSIBLE".
 *
 */

#include <iostream>

class Stack
{
public:
    Stack(int cap = 1000);
    ~Stack();
    
    void Push(char c);
    char Pop() { size--; return buffer[end--]; }
    
    // Посмотреть последний элемент
    char SeeLast() { return (IsEmpty()) ? 0 : buffer[end]; }
    
    // Проверка на пустоту
    bool IsEmpty() { return size == 0; }
    
    // Узнать размер
    int GetSize() { return size; }
    
private:
    // Переразметка памяти при переполнении буфера
    void ReAllocate();
    
    char* buffer;
    
    int capacity;
    int size;
    int end;
};

Stack::Stack(int cap)
{
    capacity = cap;
    size = 0;
    end = -1;
    buffer = new char[capacity];
}

Stack::~Stack()
{
    delete[] buffer;
}

void Stack::Push(char c)
{
    if ( end == capacity - 1 )
        ReAllocate();
    buffer[++end] = c;
    size++;
}

void Stack::ReAllocate()
{
    int new_capacity = capacity * 10;
    char* new_buffer = new char[new_capacity];
    
    for ( int i = 0; i < capacity; i++ )
        new_buffer[i] = buffer[i];
    
    delete[] buffer;
    
    buffer = new_buffer;
    capacity = new_capacity;
}

// Проверка на открывающую скобку
bool IsOpening(char bracket)
{
    return ( (bracket == '(') || (bracket == '[') || (bracket == '{'));
}

// Получение противоположной скобки
char OppositeBracket(char bracket)
{
    switch (bracket)
    {
    case '(':
        return ')';
    case '{':
        return '}';
    case '[':
        return ']';
    case ')':
        return '(';
    case '}':
        return '{';
    case ']':
        return '['; 
    }
    return 0;
}

// Формирование закрывающей последовательности
Stack* GetClosingSequence(Stack* stack)
{
    Stack* backStack = new Stack();
    char curChar = 0;
    
    while ( !stack->IsEmpty() )
    {
        curChar = stack->SeeLast();
        if ( IsOpening(curChar) )
        {
            stack->Pop();
            backStack->Push(OppositeBracket(curChar));
        }
        else
            break;
    }
    
    return backStack;
}

// Формирование открывающей последовательности
Stack* GetOpeningSequence(Stack* stack)
{
    Stack *frontStack = new Stack();
    char curChar = 0;
    
    while ( !stack->IsEmpty() )
    {
        curChar = stack->Pop();
        if ( !IsOpening(curChar) )
            frontStack->Push(OppositeBracket(curChar));
        else
        {
            frontStack->Push('0');
            return frontStack;
        }
    }
    return frontStack;
}

// Формирование полной последовательности
Stack* BuildSequence(Stack *backStack, char *input, int i, Stack *frontStack)
{
    Stack *closed = new Stack();
    
    while ( !backStack->IsEmpty() )
        closed->Push(backStack->Pop());
    
    while ( i > 0 )
        closed->Push(input[--i]);
    
    while ( !frontStack->IsEmpty() )
        closed->Push(frontStack->Pop());
    
    return closed;
}

// Получение стека с правильной последовательностью в обатном порядке
//      ( пустой стек в случае ошибки)
Stack* ReversedClosedSequence(char* input)
{
    Stack *S = new Stack();
    
    //Возвращаемый стек в случае ошибки
    Stack *impossible = new Stack();
    
    char curChar = input[0];
    int i = 0;
    char last = 0;
    
    // Заполнение стека исходной последовательностью с удалением парных скобок
    //          и выявлением ошибочной последовательности
    while ( curChar != '\0')
    {
        if ( IsOpening(curChar) )
            S->Push(curChar);
        else
        {
            if ( !S->IsEmpty() )
            {
                last = S->SeeLast();
                if ( IsOpening(last) && ( curChar == OppositeBracket(last) ) )
                    S->Pop();
                else
                    if ( IsOpening(last) && ( curChar != OppositeBracket(last) ) )
                        return impossible;
                    else
                        S->Push(curChar);
            }
            else
                S->Push(curChar);
        }
        curChar = input[++i];
    }
    
    // Формирование закрывающей последовательности
    Stack *backStack = GetClosingSequence(S);
    
    // Формирование открывающей последовательности
    Stack *frontStack = GetOpeningSequence(S);
    
    if ( frontStack->SeeLast() == '0' )
    {
        delete backStack;
        delete frontStack;
        delete S;
        return impossible;
    }
    
    // Формирование полной последовательности
    Stack *closed = BuildSequence(backStack, input, i, frontStack);
        
    delete backStack;
    delete frontStack;
    delete S;
    delete impossible;
    
    return closed;
}

// Перевод стека в строку (в обратном порядке)
char* StackToString(Stack *stack)
{
    char *str = new char[stack->GetSize() + 1];
    int i = 0;
    
    while ( !stack->IsEmpty() )
        str[i++] = stack->Pop();
    str[i] = 0;
    
    return str;
}

int main()
{
    char* input = new char[1000001];
    
    std::cin >> input;
    
    // Получение стека с правильной последовательностью в обатном порядке
    Stack* out = ReversedClosedSequence(input);
    
    if ( out->IsEmpty() )
        std::cout << "IMPOSSIBLE";
    else
    {
        // Перевод стека в строку
        char* sequence = StackToString(out);
        std::cout << sequence;
        delete[] sequence;
    }
    
    delete out;
    
    return 0;
}

