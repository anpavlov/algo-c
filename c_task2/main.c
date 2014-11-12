/*
 * author: andrey pavlov
 * group: АПО-12
 * task: 
 */

#include <stdio.h>
#include <stdlib.h>

#define unlikely(expr) __builtin_expect(!!(expr), 0)

#define ERROR_MSG "[error]"
#define STR_MAX_LENGTH 1000
#define MAX_STRINGS 1000

// Ввод массива строк
char** input_str_array();

// Удаление лишних пробелов из строк массива
char** delete_extra_spaces_arr(char **input);

// Очистка памяти
void delete_str_array(char **arr);

// Вывод массива строк
void print_str_array(char **arr);

// Удаление лишних пробелов в строке
void delete_extra_spaces(char *from, char *to);

int main()
{
    // Массив введенных строк
    char **input_strings = input_str_array();
    
    if ( unlikely( input_strings == NULL ) )
    {
        printf(ERROR_MSG);
        return 0;
    }
    
    // Строки с удаллеными пробелами
    char **edited = delete_extra_spaces_arr(input_strings);
    
    if ( unlikely( edited == NULL ) )
    {
        printf(ERROR_MSG);
        return 0;
    }
    
    // Вывод массива строк
    print_str_array(edited);
    
    // Удаление массивов
    delete_str_array(edited);
    delete_str_array(input_strings);
    
    return 0;
}

// Ввод массива строк
char** input_str_array()
{
    char **strings = (char**) calloc(MAX_STRINGS, sizeof(char*));
    
    // Если не удалось выделить память
    if ( unlikely( strings == NULL ) )
        return NULL;
    
    int i = 0;
    for ( i = 0; i < MAX_STRINGS; i++ )
    {
        strings[i] = (char*) calloc(STR_MAX_LENGTH, sizeof(char));
        
        // Если не удалось выделить память
        if ( unlikely( strings[i] == NULL ) )
            return NULL;
    }
    
    // Ввод из потока stdin пока не встретится EOF
    i = 0;
    while ( fgets(strings[i], STR_MAX_LENGTH, stdin) )
        i++;
    
    // Добавляем последней строку с EOF, чтобы можно было отследить
    // сколько строк введено (также учитываются пустые строки)
    if ( i < MAX_STRINGS )
        strings[i][0] = EOF;
    
    return strings;
}

// Очистка памяти
void delete_str_array(char **arr)
{
    if ( unlikely( arr != NULL ) )
    {
        int i = 0;
        while ( i < MAX_STRINGS )
            if ( unlikely( arr[i] != NULL ) )
                free(arr[i++]);
        free(arr);
    }
}

// Вывод массива строк
void print_str_array(char **arr)
{
    if ( unlikely( arr != NULL ) )
    {
        int i = 0;
        while ( i < MAX_STRINGS )
            if ( unlikely( arr[i] != NULL ) )
            {
                if ( arr[i][0] == EOF )
                    return;
                else
                    printf("%s", arr[i++]);
            }
    }
}

// Удаление лишних пробелов из строк массива
char** delete_extra_spaces_arr(char **input)
{
    char **edited = (char**) calloc(MAX_STRINGS, sizeof(char*));
    
    // Если не удалось выделить память
    if ( unlikely( edited == NULL ) )
        return NULL;
    
    int i = 0;
    for ( i = 0; i < MAX_STRINGS; i++ )
    {
        edited[i] = (char*) calloc(STR_MAX_LENGTH, sizeof(char));
        
        // Если не удалось выделить память
        if ( unlikely( edited[i] == NULL ) )
            return NULL;
    }
    
    // Проверки на существование строк
    if ( unlikely( input != NULL ) )
    {
        i = 0;
        while ( i < MAX_STRINGS )
            if ( unlikely( input[i] != NULL ) )
            {
                if ( input[i][0] == EOF )
                    return edited;
                else
                {
                    // Удаление лишних пробелов из строки
                    delete_extra_spaces(input[i], edited[i]);
                    i++;
                }
            }
            else
                return NULL;
    }
    else
        return NULL;
    
    return edited;
}

// Удаление лишних пробелов в строке
void delete_extra_spaces(char *from, char *to)
{
    if ( unlikely( from == NULL || to == NULL ) )
        return;
    
    int space_on = 0; // Флаг того, что пробел уже был
    int i = 0, j = 0;
    
    while ( from[i] != '\n' && from[i] != '\0' )
    {
        if ( from[i] == ' ' )
        {
            // Если пробел и флаг == 0, ставим его и копируем единственный пробел
            if ( space_on == 0)
            {
                space_on = 1;
                to[j++] = from[i++];
            }
            else
                // Если же флаг уже был = 1, то переходим к 
                // следующему символу без копирования
                i++;
        }
        else
        {
            // если буква, то сбрасываем флаг и копируем символ
            if ( space_on == 1 )
                space_on = 0;
            to[j++] = from[i++];
        }
    }
    
    // Добавляем в конец символы переноса и конца строки
    to[j++] = '\n';
    to[j] = '\0';
}
