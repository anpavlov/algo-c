/*
 *
 * author: a.pavlov
 * group: АПО-12
 * task: 3_1. Вычислить разницу глубин наивного дерева поиска и декартового дерева
 *
 */

#include <iostream>

using namespace std;

template< class T >
struct CNode
{
    T key;
    int priority;
    CNode* right;
    CNode* left;
    CNode(T value, int prio) : key(value), priority(prio), right(NULL), left(NULL) {}
    CNode(T value) : key(value), priority(0), right(NULL), left(NULL) {}
};

template< class T >
class BinaryTree
{
public:
    BinaryTree();
    ~BinaryTree();
    
    void insert(T value);
    int height() const;
    CNode<T>* find(T value);
private:
    void m_insert(CNode<T>*& node, T value);
    void m_delete(CNode<T>*& node);
    int m_height(CNode<T>* node) const;
    CNode<T>* m_find(CNode<T>* node, T value);
    
    CNode<T>* root;
};

template< class T >
class Treap
{
public:
    Treap();
    ~Treap();
    
    void insert(T value, int priority);
    int height() const;
private:
    void split(CNode<T>* node, T key, CNode<T>*& left, CNode<T>*& right);
    CNode<T>* merge(CNode<T>* left, CNode<T>* right);
    
    int m_height(CNode<T>* node) const;
    void m_delete(CNode<T>*& node);
    CNode<T>* m_findInsert(CNode<T>* node, T value, int prio);
    
    CNode<T>* root;
};

int main()
{
    int n;
    cin >> n;
    BinaryTree<int> bin_tree;
    Treap<int> treap;
    for ( int i = 0; i < n; ++i )
    {
        int val;
        int prio;
        cin >> val >> prio;
        bin_tree.insert(val);
        treap.insert(val, prio);
    }
    int diff = bin_tree.height() - treap.height();
    cout << (diff < 0 ? -diff : diff);
    return 0;
}

// ===============================================

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
int BinaryTree<T>::height() const
{
    return m_height(root);
}

template< class T >
CNode<T>* BinaryTree<T>::find(T value)
{
    return m_find(value);
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
int BinaryTree<T>::m_height(CNode<T>* node) const
{
    if ( !node )
        return 0;
    return max(m_height(node->right), m_height(node->left)) + 1;
}

template< class T >
CNode<T>* BinaryTree<T>::m_find(CNode<T>* node, T value)
{
    if ( !node )
        return NULL;
    if ( node->key == value )
        return node;
    if ( node->key > value )
        return m_find(node->left, value);
    else
        return m_find(node->right, value);
}

// ============================================

template< class T >
Treap<T>::Treap()
    : root(NULL)
{
}

template< class T >
Treap<T>::~Treap()
{
    m_delete(root);
}

template< class T >
void Treap<T>::insert(T value, int priority)
{
    CNode<T>* newNode = new CNode<T>(value, priority);
    CNode<T>* parent = NULL;
    parent = m_findInsert(root, value, priority);
    
    if ( !parent )
    {
        if ( !root )
        {
            root = newNode;
            return;
        }
        else
        {
            split(root, value, newNode->left, newNode->right);
            root = newNode;
            return;
        }
    }
    
    if ( parent->key > value )
    {
        split(parent->left, value, newNode->left, newNode->right);
        parent->left = newNode;
    }
    else
    {
        split(parent->right, value, newNode->left, newNode->right);
        parent->right = newNode;
    }
}

template< class T >
int Treap<T>::height() const
{
    return m_height(root);
}

template< class T >
void Treap<T>::split(CNode<T>* node, T key, CNode<T>*& left, CNode<T>*& right)
{
    if ( !node )
    {
        left = NULL;
        right = NULL;
    }
    else
    {
        if ( node->key <= key )
        {
            split(node->right, key, node->right, right);
            left = node;
        }
        else
        {
            split(node->left, key, left, node->left);
            right = node;
        }
    }
}

template< class T >
CNode<T>* Treap<T>::merge(CNode<T>* left, CNode<T>* right)
{
    if ( !left || ! right )
        return !left ? right : left;
    if ( left->priority > right->priority )
    {
        left->right = merge(left->right, right);
        return left;
    }
    right->left = merge(left, right->left);
    return right;
}

template< class T >
CNode<T>* Treap<T>::m_findInsert(CNode<T>* node, T value, int prio)
{
    if ( !node ) // когда дерево пустое
        return NULL;
    if ( node->priority < prio ) // выше корня
        return NULL;
    if ( node->key > value )
    {
        if ( !node->left )
            return node;
        if ( node->left->priority < prio )
            return node;
        return m_findInsert(node->left, value, prio);
    }
    else
    {
        if ( !node->right )
            return node;
        if ( node->right->priority < prio )
            return node;
        return m_findInsert(node->right, value, prio);
    }
}


template< class T >
int Treap<T>::m_height(CNode<T>* node) const
{
    if ( !node )
        return 0;
    return max(m_height(node->right), m_height(node->left)) + 1;
}

template< class T >
void Treap<T>::m_delete(CNode<T>*& node)
{
    if ( node->left )
        m_delete(node->left);
    if ( node->right )
        m_delete(node->right);
    if ( node )
        delete node;
}
