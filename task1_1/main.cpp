/*
 *
 * author: a.pavlov
 * group: АПО-12
 * task: 1_2. Вывести разложение натурального числа n на простые множители.
 * Простые множители должны быть упорядочены по возрастанию и разделены пробелами.
 *
 */

#include <iostream>

using namespace std;

// Вычисляем множители
int findPrimeMultiples(bool* arr, int n, int* output)
{
    int k = 0; // счетчик для массива output
    for( int i = 2; i <= n; i++ ) {
        if( arr[i] ) {
            for( int j = i * i; j <= n; j += i ) {
                arr[j] = false;
            }
            // Если число простое, пробуем делить на него
            while( n % i == 0) {
                output[k] = i;
                k++;
                n /= i;
            }
        }
    }
    return k;
}

int main()
{
    int n = 0;

    // Ввод n
    cin >> n;

    // Если ввели 1, то выводим 1 и завершаем программу
    if( n == 1 ) {
        cout << n;
        return 0;
    }

    bool* isPrime = new bool[n+1];

    int* output = new int[n/2];

    // Инициализвация
    for( int i = 0; i <= n; i++ ) {
        isPrime[i] = true;
    }

    // Вычисляем множители
    int PrimeMultiplesAmount = findPrimeMultiples(isPrime, n, output);

    // Вывод без последнего числа
    int i = 0;
    for( i = 0; i < PrimeMultiplesAmount - 1; i++ )
    {
        cout << output[i] << " ";
    }
    // Вывод последнего числа отдельно, чтобы после него не было пробела
    cout << output[i];

    delete [] isPrime;
    delete [] output;
    return 0;
}
