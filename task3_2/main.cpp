/*
 *
 * author: a.pavlov
 * group: АПО-12
 * task: 2_3. Выведите элементы в порядке post-order (снизу вверх)
 *
 */

#include <iostream>

using namespace std;

template< class T >
struct CNode
{
    T key;
    CNode* right;
    CNode* left;
    CNode(T value) : key(value), right(NULL), left(NULL) {}
};

template< class T >
class BinaryTree
{
public:
    BinaryTree();
    ~BinaryTree();
    
    void insert(T value);
    void downTop(void (*nodeHandler)(CNode<T>*&));
private:
    void m_insert(CNode<T>*& node, T value);
    void m_delete(CNode<T>*& node);
    void m_downTop(CNode<T>*& node, void (*nodeHandler)(CNode<T>*&));
    
    CNode<T>* root;
};

template< class T >
void print(CNode<T>*& node);

int main()
{
    int n;
    cin >> n;
    BinaryTree<int> tree;
    for ( int i = 0; i < n; ++i )
    {
        int val;
        cin >> val;
        tree.insert(val);
    }
    tree.downTop(print);
    return 0;
}

template< class T >
void print(CNode<T>*& node)
{
    cout << node->key << " ";
}

template< class T >
BinaryTree<T>::BinaryTree()
    : root(NULL)
{
}

template< class T >
BinaryTree<T>::~BinaryTree()
{
    m_delete(root);
}

template< class T >
void BinaryTree<T>::insert(T value)
{
    m_insert(root, value);
}

template< class T >
void BinaryTree<T>::downTop(void (*nodeHandler)(CNode<T>*&))
{
    m_downTop(root, nodeHandler);
}

template< class T >
void BinaryTree<T>::m_insert(CNode<T>*& node, T value)
{
    if ( !node )
    {
        node = new CNode<T>(value);
        return;
    }
    if ( node->key > value )
        m_insert(node->left, value);
    else
        m_insert(node->right, value);
}

template< class T >
void BinaryTree<T>::m_delete(CNode<T>*& node)
{
    if ( node->left )
        m_delete(node->left);
    if ( node->right )
        m_delete(node->right);
    if ( node )
        delete node;
}

template< class T >
void BinaryTree<T>::m_downTop(CNode<T>*& node, void (*nodeHandler)(CNode<T>*&))
{
    if ( node->left )
        m_downTop(node->left, nodeHandler);
    if ( node->right )
        m_downTop(node->right, nodeHandler);
    if ( node )
        nodeHandler(node);
}
