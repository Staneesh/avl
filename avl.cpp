#include "avl.h"

template<typename Key, typename Info>
void AVL<Key, Info>::updateHeight(AVL<Key, Info>::Node* s)
{
    int LH = -1;
    int RH = -1;
    if (s->left) LH = s->left->height;
    if (s->right) LH = s->right->height;
    
    s->height = max(LH, RH) + 1;
}

template<typename Key, typename Info>
typename AVL<Key, Info>::Node* AVL<Key, Info>::rotateL(AVL<Key, Info>::Node* s)
{
    auto z = s->right;

    auto t23 = z->left;

    s->right = t23;
    z->left = s;

    updateHeight(s);
    updateHeight(z);

    return z;
}


template<typename Key, typename Info>
typename AVL<Key, Info>::Node* AVL<Key, Info>::rotateR(AVL<Key, Info>::Node* s)
{
    auto z = s->left;

    auto t23 = z->right;

    s->left = t23;
    z->right = s;

    updateHeight(s);
    updateHeight(z);

    return z;
}

int abs(int a)
{
    return a > 0 ? a : -a;
}

template<typename Key, typename Info>
void AVL<Key, Info>::rebalance(Node* s)
{
    if (abs(s->balance) > 1)
    {
        if (s->balance < 0)
        {
            rotateR(s);
        }
        else
        {
            rotateL(s);
        }
    }

}

template<typename Key, typename Info>
void AVL<Key, Info>::insertRECURSION(bool lastTimeGoneLeft, const Key& k, const Info& i,
                                     Node* s, Node* prev)
{
    //cout<<"inserting("<<k<<","<<i<<")"<<endl;;
    if (s)
    {
        int d = k - s->k;
        if (d == 0) return;

        if (d > 0) //k > s->k
        {
            insertRECURSION(false, k, i, s->right, s);
        }
        else
        {
            insertRECURSION(true, k, i, s->left, s);
        }
    }
    else
    {
        if (root == 0)
        {
            root = new Node(k, i);
            return;
        }


        if (lastTimeGoneLeft)
        {
            prev->left = new Node(k, i);
            if (prev->right) ++prev->height;
            return;
        }
        else
        {
            prev->right = new Node(k, i);
            if (prev->left) ++prev->height;
            return;
        }


    }

    int LH = -1;
    if (s->left) LH = s->left->height;
    int RH = -1;
    if (s->right) RH = s->right->height;
    
    s->height = max(LH, RH) + 1;

    int curB = RH - LH; 

    int leftKey = 100000, rightKey = leftKey;
    if (s->left) leftKey = s->left->k;
    if (s->right) rightKey = s->right->k;
    
    
#if 1
    if (curB > 1 && k < leftKey)  
    {
        auto res = rotateL(prev);
        if (prev == root) root = res;
        
    }
    
    if (curB < -1 && k > rightKey)  
    {
        auto res = rotateR(prev);  
        if (prev == root) root = res;
    }
    if (curB > 1 && k > leftKey)  
    {  
        prev->left = rotateL(prev->left);  
        auto res = rotateR(prev);  
        if (prev == root) root = res;        
    }  

    if (curB < -1 && k < rightKey)  
    {  
        prev->right = rotateR(prev->right);  
        auto res = rotateL(prev);  
        if (prev == root) root = res;
    }
#endif    
}

template<typename Key, typename Info>
void AVL<Key, Info>::printNode(const Node* n) const
{
    cout<<n->k<<":"<<n->height;
}

template<typename Key, typename Info>
void AVL<Key, Info>::printRECURSION(Node* n, int h)
{
    if (n->right)
    {
        printRECURSION(n->right, h + 1);
    }
    for (int i = 0; i < h; i++)
    {
        cout<<"-|-";
    }
    printNode(n);

    cout<<endl;
    if (n->left)
    {
        printRECURSION(n->left, h + 1);
    }
}


template<typename Key, typename Info>
void AVL<Key, Info>::insert(const Key& k, const Info& i)
{
    insertRECURSION(false, k, i, root, root);
}

template<typename Key, typename Info>
void AVL<Key, Info>::print()
{
    if (root)
    {
        printRECURSION(root, 0);
    }
}
