/*
 *
 * author: a.pavlov
 * group: АПО-12
 * task: 3_4. Закраска прямой 2.
 * На числовой прямой окрасили N отрезков.
 * Известны координаты левого и правого концов
 * каждого отрезка (Li и Ri). Найти сумму длин
 * частей числовой прямой, окрашенных ровно
 * в один слой.
 *
 */

#include <iostream>

enum PointType { START, FINISH };

struct Point {
    //Point() {}
    //Point(int nX, PointType t) : x(nX), type(t) {}
    void Set(int nX, PointType t) { x = nX; type = t; }
    int x;
    PointType type;
};

bool operator<= (Point& point1, Point& point2);

void mergeSort(Point *&arr, int start, int finish);

int input(Point *&arr);

int countOneThicknessLength(CArray<Point>& arr);

int main()
{
    Point* arr;
    
    int n = input(arr);
    
    mergeSort(arr, 0, n - 1);
    
    int length = countOneThicknessLength(arr);
    
    std::cout<<length;
    
    return 0;
}

int countOneThicknessLength(CArray<Point>& arr)
{
    bool isOne = false;
    int thickness = 0;
    int oneBegin = 0;
    int length = 0;
    for ( int i = 0; i < arr.GetSize(); ++i )
    {
        if ( arr[i].type == START )
            ++thickness;
        else
            --thickness;
        if ( thickness != 1 )
        {
            if ( isOne == true )
            {
                isOne = false;
                length += (arr[i].x - oneBegin);
            }
        }
        else
        {
            if ( isOne == false )
            {
                isOne = true;
                oneBegin = arr[i].x;
            }
        }
    }
    return length;
}

bool operator<= (Point& point1, Point& point2)
{
    return point1.x <= point2.x;
}

int input(Point*& arr)
{
    int n;
    std::cin >> n;
    arr = new Point[2*n];
    int start, finish;
    for ( int i = 0; i < 2*n; i += 2 )
    {
        std::cin >> start >> finish;
        arr[i].Set(start, START);
        arr[i + 1].Set(finish, FINISH);
    }
    return n;
}

void mergeSort(Point*& arr, int start, int finish)
{
    if ( finish - start == 0 )
        return;
    
    CArray<T> half1(arr, 0, arr.GetSize() / 2 - 1);
    CArray<T> half2(arr, arr.GetSize() / 2, arr.GetSize() - 1);
    
    mergeSort(half1);
    mergeSort(half2);
    
    int j = 0, k = 0;
    for ( int i = 0; i < arr.GetSize(); ++i )
    {
        if ( j < half1.GetSize() && k < half2.GetSize() )
        {
            if ( half1[j] <= half2[k] )
            {
                arr[i] = half1[j];
                ++j;
            }
            else
            {
                arr[i] = half2[k];
                ++k;
            }
        }
        else
        {
            if ( j < half1.GetSize() )
            {
                arr[i] = half1[j];
                ++j;
            }
            else
            {
                arr[i] = half2[k];
                ++k;
            }
        }
    }
}
