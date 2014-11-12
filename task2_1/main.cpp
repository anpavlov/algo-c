#include <iostream>

template<class T>
class CArray
{
public:
    CArray(int cap = 50);
    ~CArray();
    
    void Add(T elem);
    T& operator []();
    
private:
    Reallocate();
    
    T* buffer;
    int capacity;
    int size;
};

template<class T>
CArray::CArray(int cap)
    : capacity(cap)
    , size(0)
{
    buffer = new T[capacity];
}

template<class T>
void CArray

int main()
{
    //cout << "Hello World!" << endl;
    return 0;
}

