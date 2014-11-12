/*
 *
 * author: a.pavlov
 * group: АПО-12
 * task: 3_4. Дан отсортированный массив целых
 * чисел A[0..n-1] и массив целых чисел B[0..m-1].
 * Для каждого элемента массива B[i] найдите минимальный
 * индекс элемента массива A[k], ближайшего по значению
 * к B[i]. Время работы поиска для каждого
 * элемента B[i]: O(log(k)).
 *
 */

#include <iostream>

// Ввод целочисленного массива
void intArrayInput(int* arr, int n) {
    for( int i = 0; i < n; i++ ) {
        std::cin >> arr[i];
    }
}

// Вывод целочисленного массива
void intArrayOutput(int* arr, int n)
{
    for ( int i = 0; i < n - 1; i++ )
        std::cout << arr[i] << " ";
    std::cout << arr[n - 1];
}

// Нахождение ближайшего к elem элемента в массиве A
int findElement(int* A, int n, int elem)
{
    // Проверка, если элемент за границами
    if ( elem <= A[0] ) return 0;
    if ( elem >= A[n-1] ) return n - 1;
    
    // Поиск границ для последующего поиска
    int first = 0;
    int last = 1;
    for ( int i = 1; i < n; i*=2 )
        if ( elem <= A[i] )
        {
            last = i;
            break;
        }
        else
            first = i;
    
    // Если найденные границы являются соседними
    if ( last - first == 1 )
        return ( (A[last] - elem) < (elem - A[first]) ) ? last : first;
    
    // Двоичный поиск
    int mid = 0;
    while ( first < last )
    {
        mid  = (first + last) / 2;
        if ( elem <= A[mid] )
            last = mid;
        else first = mid + 1;
    }
    
    // Сравнение с найденным и соседним снизу 
    if ( (A[last] - elem) < (elem - A[last - 1]) )
        return last;
    else
        return last - 1;
}

// Нахождение всех элементов B в A
void findElements(int* A, int* B, int n, int m, int* output)
{
    for (int i = 0; i < m; i++ )
        output[i] = findElement(A, n, B[i]);
}

int main()
{
    int n = 0;

    // Ввод n
    std::cin >> n;

    int* A = new int[n];

    // Ввод первого массива
    intArrayInput(A, n);

    int m = 0;

    // Ввод m
    std::cin >> m;

    int* B = new int[m];

    // Ввод второго массива
    intArrayInput(B, m);

    
    // Выходной массив
    int* output = new int[m];
    
    // Нахождение всех элементов B в A
    findElements(A, B, n, m, output);
    
    // Вывод
    intArrayOutput(output, m);
    
    delete[] A;
    delete[] B;
    delete[] output;

    return 0;
}

