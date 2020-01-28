#include "avl.h"


template<typename Key, typename Info>
void AVL<Key, Info>::rotateL(AVL<Key, Info>::Node* s)
{
    auto z = s->right;

    auto t23 = z->left;

    s->right = t23;
    z->left = s;


    if (z->balance == 0)
    {
        s->balance = 1;
        z->balance = -1;
    }
    else
    {
        s->balance = 0;
        z->balance = 0;
    }
}


template<typename Key, typename Info>
void AVL<Key, Info>::rotateR(AVL<Key, Info>::Node* s)
{
    auto z = s->left;

    auto t23 = z->right;

    s->left = t23;
    z->right = s;


    if (z->balance == 0)
    {
        s->balance = -1;
        z->balance = 1;
    }
    else
    {
        s->balance = 0;
        z->balance = 0;
    }
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


        int increased = 0;
        if (lastTimeGoneLeft)
        {
            prev->left = new Node(k, i);
            increased = -1;
        }
        else
        {
            prev->right = new Node(k, i);
            increased = 1;
        }

        prev->balance += increased;
    }


    //NOTE: rebalancing
    auto l = prev->left;
    auto r = prev->right;
    auto curB = prev->balance;
    
    if (curB > 1 && k < l->k)  
        return rotateR(prev);  
  
    if (curB < -1 && k > r->k)  
        return rotateR(prev);  
  
    if (curB > 1 && k > l->k)  
    {  
        rotateL(l);  
        rotateR(prev);  
    }  

    if (curB < -1 && k < r->k)  
    {  
        rotateR(r);  
        rotateL(prev);  
    }  
}

template<typename Key, typename Info>
void AVL<Key, Info>::printNode(const Node* n) const
{
    cout<<n->k<<endl;
}

template<typename Key, typename Info>
void AVL<Key, Info>::printRECURSION(Node* n)
{
    cout<<"GOING L:"<<endl;
    printRECURSION(n ->left);
    cout<<"GOING R:"<<endl;
    printRECURSION(n ->right);
}


template<typename Key, typename Info>
void AVL<Key, Info>::insert(const Key& k, const Info& i)
{
    insertRECURSION(false, k, i, root, root);
}

template<typename Key, typename Info>
void AVL<Key, Info>::print()
{
    printRECURSION(root);
}
