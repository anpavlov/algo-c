/*
 * author: andrey pavlov
 * group: АПО-12
 * task: Составить программу для перевода чисел из системы счисления
 * по основанию P в систему счисления по основанию Q,
 * где 2 меньше или равно Q меньше P меньше или равно 36.
 * Значения P, Q и строковое представление S числа в исходной
 * системе счисления вводятся с клавиатуры в следующем порядке: P Q S
 * Процедура перевода не может использовать соответствующей функции
 * системной библиотеки и должна быть оформлена в виде отдельной функции,
 * на вход которой подаются значения P, Q и S, размещенные в
 * динамической памяти. На выход функция должна возвращать строковое
 * представление S1 числа в целевой системе счисления. Программа
 * должна уметь обрабатывать ошибки во входных данных. В случае
 * возникновения ошибки нужно вывести в поток стандартного вывода
 * сообщение "[error]" и завершить выполнение программы.
 */

// 2<=Q<P<=36

#include <stdio.h>
#include <stdlib.h>

#define unlikely(expr) __builtin_expect(!!(expr), 0)

//#define 

#define INPUT_STR_MAX_LENGTH 100000

#define ERROR_MSG "[error]"

//Вычисение длины строки
size_t string_length(const char* str) {
    if ( unlikely( str == NULL ) )
        return 0;
    size_t i = 0;
    for( ; str[i] != '\0'; i++ );
    return i;
}

// Отображение строки (возвращает true, если все прошло успешно)
int revert_string(char* str, int length)
{
    if ( unlikely( str == NULL ) )
        return 1;
    
    int i = 0, j = length - 1;
    char temp = 0;
    
    for ( i = 0; i < j; i++, j--)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
    return 0;
}

//Вычисление числого эквивалента цифры
int digit_to_decimal(char input_char, int from)
{    
    // 10 - количество цифр
    
    // Если строчная буква
    if ( (input_char >= 'a') && (input_char < (from - 10 + 'a')) )
        return input_char - 'a' + 10;
    
    // Если прописная
    if ( (input_char >= 'A') && (input_char < (from - 10 + 'A')) )
        return input_char - 'A' + 10;
    
    // Если цифра
    if ( (input_char >= '0') && (input_char < from + '0') )
        return input_char - '0';
    
    // Иначе неверный символ
    return -1;
}

// Возведение целого числа в натуральную степень
__int64_t power(int base, int degree)
{
    __int64_t sum = 1, i = 0;
    for ( i = 0; i < degree; i++ )
        sum *= base;
    return sum;
}

// Перевод в десятичную систему
__int64_t to_decimal(int from, char* from_string)
{
    if ( unlikely( from_string == NULL ) )
        return -1;
    
    char current_digit = from_string[0];
    int decimal_digit = 0;
    __int64_t decimal_number = 0;
    int i = 0;
    int from_string_length = string_length(from_string);
    
    for ( i = 0; i < from_string_length; i++ )
    {
        current_digit = from_string[i];
        decimal_digit = digit_to_decimal(current_digit, from);
        
        if ( unlikely(decimal_digit == -1) )
             return -1;
        
        decimal_number += decimal_digit * power(from, from_string_length - i - 1);
    }
    return decimal_number;
}

// Перевод из десятичной системы в любую
char* to_any(int to, __int64_t decimal)
{
    char* result = (char*) calloc(INPUT_STR_MAX_LENGTH, 1);
    
    if ( unlikely( result == NULL ) )
        return NULL;
    
    int mod = 0;
    int i = 0;
    
    while ( decimal != 0 )
    {
        mod = decimal % to;
        decimal /= to;
        if ( mod > 9 )
            result[i] = mod + 'A' - 10;
        else
            result[i] = mod + '0';
        i++;
    }
    
    if ( unlikely(revert_string(result, i) != 0) )
        return NULL;
    
    return result;
}

// Перевод
char* transfer(int from, int to, char* from_string)
{    
    if ( unlikely( from_string == NULL ) )
        return NULL;
    
    // Перевод числа в десятичную систему
    __int64_t decimal_number = to_decimal(from, from_string);
    
    // Если возникли ошибки
    if ( unlikely(decimal_number == -1) )
        return NULL;
    
    // Финальный перевод из десятичной в необходимую
    char* result = to_any(to, decimal_number);
    
    return result;
}

int main()
{
    int P = 0, Q = 0;
    char *S = (char*) calloc(INPUT_STR_MAX_LENGTH, 1);
    
    if ( unlikely( S == NULL ) )
        return 0;
    
    if ( unlikely( scanf("%d %d %s", &P, &Q, S) != 3 ) )
    {
        printf(ERROR_MSG);
        free(S);
        return 0;
    }
    
    // Проверка на соответсвие условиям
    if ( unlikely( (Q > P) || (Q > 36) || (P > 36) || (P < 2) || (Q < 2)) )
    {
        printf(ERROR_MSG);
        free(S);
        return 0;
    }
    
    // Перевод числа
    char* result = transfer(P, Q, S);
    
    if ( unlikely( result == NULL ) )
        printf(ERROR_MSG);
    else
        printf("%s",result);

    free(S);
    free(result); 
    
    return 0;
}

