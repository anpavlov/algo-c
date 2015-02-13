#include <iostream>
#include <vector>
#include <string>

#define INITINAL_SIZE 8
#define GROW_FACTOR 2
#define DELETED "!deleted"

using namespace std;

int Hash(const string& data, int tableSize)
{
    int hash = 0;
    for ( unsigned int i = 0; i < data.size(); ++i )
        hash = (hash * 127 + data[i]) % tableSize;
    return hash;
}

template< class T >
class CHashTable
{
public:
    CHashTable();
    ~CHashTable();
    
    bool Has(const T& data) const;
    bool Add(const T& data);
    bool Delete(const T& data);
    
private:
    vector<T> table;
    unsigned int keysCount;
    
    int hash(int hashVal, int p) const;
    
    // bool = есть или нет. where = если есть - где, нет - куда вставить
    bool has(const T& data, int hashVal, int& where) const;
    void growTable();
};

int main()
{
    CHashTable<string> table;
    char operation;
    string word;
    
    while ( cin >> operation >> word )
    {
        switch (operation)
        {
        case '+':
            cout << (table.Add(word) ? "OK" : "FAIL") << endl;
            break;
        case '-':
            cout << (table.Delete(word) ? "OK" : "FAIL") << endl;
            break;
        case '?':
            cout << (table.Has(word) ? "OK" : "FAIL") << endl;
            break;
        }
    }
    return 0;
}

template< class T >
CHashTable<T>::CHashTable()
    : keysCount(0)
{
    table.resize(INITINAL_SIZE);
}

template< class T >
CHashTable<T>::~CHashTable()
{
}

template< class T >
bool CHashTable<T>::Has(const T& data) const
{
    int hash = Hash(data, table.size());
    int where;
    return has(data, hash, where);
}

template< class T >
bool CHashTable<T>::Add(const T& data)
{
    if ( 4 * (keysCount + 1) > 3 * table.size() )
        growTable();
    
    int hashVal = Hash(data, table.size());
    int where;
    
    if ( has(data, hashVal, where) )
        return false;
    
    table[where] = data;
    ++keysCount;
    return true;
}

template< class T >
bool CHashTable<T>::Delete(const T& data)
{
    int hashVal = Hash(data, table.size());
    int where;
    if ( !has(data, hashVal, where) )
        return false;
    table[where] = DELETED;
    --keysCount;
    return true;
}

template< class T >
bool CHashTable<T>::has(const T& data, int hashVal, int& where) const
{
    int p = 1;
    int index = hashVal;
    where = -1;
    for ( int i = 0; i < table.size(); ++i )
    {
        index = hash(hashVal, p++);
        if ( index > table.size() - 1 )
            index = index % table.size();
        if ( table[index] == DELETED )
            where = index;
        else if ( table[index] == "" )
        {
            if ( where == -1 )
                where = index;
            return false;
        }
        if ( table[index] == data )
        {
            where = index;
            return true;
        }
    }
    return false;
}

template< class T >
int CHashTable<T>::hash(int hashVal, int p) const
{
    return (hashVal + p * (p + 1) / 2) % table.size();
}

template< class T >
void CHashTable<T>::growTable()
{
    /*vector<T> newTable(table.size() * GROW_FACTOR);
    int hashVal;
    int where, p, index;
    for ( int i = 0; i < table.size(); ++i )
        if ( table[i] != "" && table[i] != DELETED )
        {            
            hashVal = Hash(table[i], newTable.size());
            
            p = 1;
            index = hashVal;
            where = -1;
            while ( newTable[index] != "" )
            {
                index = hash(hashVal, ++p);
                if ( index > newTable.size() - 1 )
                    index = index % newTable.size();
            } 
            where = index;
            
            newTable[where] = table[i];
        }
    table = newTable;*/
    vector<T> oldTable = table;
    vector<T> newTable(table.size() * GROW_FACTOR);
    table = newTable;
    for ( int i = 0; i < oldTable.size(); ++i )
        if ( oldTable[i] != "" && oldTable[i] != DELETED )
            Add(oldTable[i]);
    
}

