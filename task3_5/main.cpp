/*
 *
 * author: a.pavlov
 * group: АПО-12
 * task: 5_2. Порядковые статистики
 *
 */

#include <iostream>

using namespace std;

template< class T >
struct CNode
{
    T key;
    int height;
    int size;
    CNode* right;
    CNode* left;
    CNode(T value) : key(value), height(1), size(1), right(NULL), left(NULL) {}
};

template< class T >
class AVLTree
{
public:
    AVLTree();
    ~AVLTree();
    
    void insert(T value);
    void del(T value);
    int height() const;
    T kthOrderStatistics(int k);
private:
    int m_height(CNode<T>* node) const;
    int m_balanceFactor(CNode<T>* node);
    void m_fixHeight(CNode<T>* node);
    
    void m_fixSize(CNode<T>* node);
    int m_size(CNode<T>* node);
    T m_kthOrderStatistics(CNode<T>* node, int k);
    
    CNode<T>* findMin(CNode<T>* node);
    void deleteMin(CNode<T>*& node);
    
    void rotateRight(CNode<T>*& node);
    void rotateLeft(CNode<T>*& node);
    void balance(CNode<T>*& node);
    
    void m_insert(CNode<T>*& node, T value);
    void m_del(CNode<T>*& node, T value);
    void m_delete(CNode<T>* node);
    
    CNode<T>* root;
};

int main()
{
    int n;
    cin >> n;
    AVLTree<int> AVL;
    int val, k;
    for ( int i = 0; i < n; ++i )
    {
        cin >> val >> k;
        if ( val < 0 )
            AVL.del(-val);
        else
            AVL.insert(val);
        cout << AVL.kthOrderStatistics(k) << endl;
    }
    return 0;
}

template< class T >
AVLTree<T>::AVLTree()
    : root(NULL)
{
}

template< class T >
AVLTree<T>::~AVLTree()
{
    m_delete(root);
}

template< class T >
void AVLTree<T>::insert(T value)
{
    m_insert(root, value);
}

template< class T >
void AVLTree<T>::del(T value)
{
    m_del(root, value);
}

template< class T >
int AVLTree<T>::height() const
{
    return m_height(root);
}

template< class T >
T AVLTree<T>::kthOrderStatistics(int k)
{
    return m_kthOrderStatistics(root, k);
}

template< class T >
int AVLTree<T>::m_height(CNode<T>* node) const
{
    return node ? node->height : 0;
}

template< class T >
CNode<T>* AVLTree<T>::findMin(CNode<T>* node)
{
    return node->left ? findMin(node->left) : node;
}

template< class T >
void AVLTree<T>::deleteMin(CNode<T>*& node)
{
    if ( !(node->left) )
    {
        node = node->right;
        return;
    }
    deleteMin(node->left);
    balance(node);
}

template< class T >
void AVLTree<T>::rotateRight(CNode<T>*& node)
{
    CNode<T>* leftChild = node->left;
    node->left = leftChild->right;
    leftChild->right = node;
    m_fixHeight(node);
    m_fixHeight(leftChild);
    node = leftChild;
}

template< class T >
void AVLTree<T>::rotateLeft(CNode<T>*& node)
{
    CNode<T>* rigthChild = node->right;
    node->right = rigthChild->left;
    rigthChild->left = node;
    m_fixHeight(node);
    m_fixHeight(rigthChild);
    node = rigthChild;
}

template< class T >
void AVLTree<T>::balance(CNode<T>*& node)
{
    m_fixHeight(node);
    if ( m_balanceFactor(node) == 2 )
    {
        if ( m_balanceFactor(node->right) < 0 )
            rotateRight(node->right);
        rotateLeft(node);
        return;
    }
    if ( m_balanceFactor(node) == -2 )
    {
        if ( m_balanceFactor(node->left) > 0 )
            rotateLeft(node->left);
        rotateRight(node);
    }
}

template< class T >
void AVLTree<T>::m_insert(CNode<T>*& node, T value)
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
    balance(node);
}

template< class T >
void AVLTree<T>::m_del(CNode<T>*& node, T value)
{
    if ( !node )
        return;
    if ( node->key > value )
        m_del(node->left, value);
    else
    {
        if ( node->key < value )
            m_del(node->right, value);
        else // node->key == value
        {
            if ( !(node->right) )
            {
                CNode<T>* leftChild = node->left;
                delete node;
                node = leftChild;
                return;
            }
            CNode<T>* min = findMin(node->right);
            deleteMin(node->right);
            min->right = node->right;
            min->left = node->left;
            delete node;
            node = min;
        }
    }
    balance(node);
}

template< class T >
int AVLTree<T>::m_balanceFactor(CNode<T>* node)
{
    return m_height(node->right) - m_height(node->left);
}

template< class T >
void AVLTree<T>::m_fixHeight(CNode<T>* node)
{
    int heightLeft = m_height(node->left);
    int heightRight = m_height(node->right);
    node->height = max(heightLeft, heightRight) + 1;
    m_fixSize(node);
}

template< class T >
void AVLTree<T>::m_fixSize(CNode<T>* node)
{
    int sizeLeft = m_size(node->left);
    int sizeRight = m_size(node->right);
    node->size = sizeLeft + sizeRight + 1;
}

template< class T >
int AVLTree<T>::m_size(CNode<T>* node)
{
    return node ? node->size : 0;
}

template< class T >
T AVLTree<T>::m_kthOrderStatistics(CNode<T>* node, int k)
{
    if ( k == m_size(node->left) )
        return node->key;
    if ( k < m_size(node->left) )
        return m_kthOrderStatistics(node->left, k);
    if ( k > m_size(node->left) )
        return m_kthOrderStatistics(node->right, k - m_size(node->left) - 1);
}

template< class T >
void AVLTree<T>::m_delete(CNode<T>* node)
{
    if ( node->left )
        m_delete(node->left);
    if ( node->right )
        m_delete(node->right);
    if ( node )
        delete node;
}
