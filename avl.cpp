#include "avl.h"

template<typename Key, typename Info>
void AVL<Key, Info>::clearRECURSION(AVL<Key, Info>::Node* s)
{
    if (!s) return;

    if (s->left) clearRECURSION(s->left);
    if (s->right) clearRECURSION(s->right);

    delete s;
}

template<typename Key, typename Info>
void AVL<Key, Info>::updateRECURSION(AVL<Key, Info>::Node* s, const Key& k, const Info& i)
{
    if (!s) return;

    if (s->k == k)
    {
        s->i = i;
        return;
    }
    
    if (s->left) clearRECURSION(s->left);
    if (s->right) clearRECURSION(s->right);

}

template<typename Key, typename Info>
void AVL<Key, Info>::clear()
{
    clearRECURSION(root);
}

template<typename Key, typename Info>
void AVL<Key, Info>::update(const Key& k, const Info& i)
{
    updateRECURSION(root, k, i);
}


template<typename Key, typename Info>
AVL<Key, Info>::~AVL()
{
    clear();
}

template<typename Key, typename Info>
void AVL<Key, Info>::updateHeight(AVL<Key, Info>::Node* s)
{
    if (!s) return;
              
    int LH = 0;
    int RH = 0;
    if (s->left) LH = s->left->height;
    if (s->right) RH = s->right->height;
    
    s->height = max(LH, RH) + 1;
}

template<typename Key, typename Info>
bool AVL<Key, Info>::findKeyRECURSIVE(Node* n, const Key& k)
{
    if (!n) return 0;

    if (k == n->key) return 1;

    if (k < n->k && n->left)
        findKeyRECURSIVE(n->left, k);

    if (k > n->k && n->right)
        findKeyRECURSIVE(n->right, k);
}

template<typename Key, typename Info>
bool AVL<Key, Info>::checkKey(const Key& k)
{
    return findKeyRECURSIVE(root, k);
}
    
template<typename Key, typename Info>
int AVL<Key, Info>::balance(const AVL<Key, Info>::Node* s) const
{
    if (!s) return 0;
    
    int LH = 0;
    int RH = 0;
    if (s->left) LH = s->left->height;
    if (s->right) RH = s->right->height;

    return  (RH - LH);
}


template<typename Key, typename Info>
int AVL<Key, Info>::heightOfSubtree(const AVL<Key, Info>::Node* s) const 
{
    if (s) return s->height;
    return 0;
}

template<typename Key, typename Info>
typename AVL<Key, Info>::Node* AVL<Key, Info>::rotateL(AVL<Key, Info>::Node* s)
{
    auto z = s->right;

    auto t23 = z->left;
z->left = s;

    s->right = t23;
    
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
typename AVL<Key, Info>::Node* AVL<Key, Info>::insertRECURSION(bool lastTimeGoneLeft, const Key& k, const Info& i,
                                     Node* s, Node* prev)
{
    if (s)
    {
        int d = k - s->k;
        if (d == 0) return (s);

        if (d < 0) //k > s->k
        {
            s->left = insertRECURSION(false, k, i, s->left, s);
        }
        else
        {
            s->right = insertRECURSION(true, k, i, s->right, s);
        }
    }
    else
    {
        return (new Node(k, i));
    }

    updateHeight(s);
    int curB = -balance(s); 



    
    int leftKey = 100000, rightKey = -leftKey;
    if (s->left) leftKey = s->left->k;
    if (s->right) rightKey = s->right->k;

    #define DEB 0
#if DEB
    int SPECJAL = 6;
    if (k == SPECJAL)
    {
        cout<<"SPECJAL"<<endl;
        cout<<"B:"<<curB<<endl;
        cout<<"LK:"<<leftKey<<" RK:"<<rightKey<<" CURK:"<<s->k<<endl;
        print();

    }
#endif
    if (curB > 1 && k < leftKey)  
    {
#if DEB
        if (k == SPECJAL)
        {
            cout<<"Entering 1"<<endl;
        }
#endif   
        return rotateR(s);
    }
    
    if (curB < -1 && k > rightKey)  
    {
#if DEB
        if (k == SPECJAL)
        {
            cout<<"Entering 2"<<endl;
        }

#endif
        return rotateL(s);
        
    }
    if (curB > 1 && k > leftKey)  
    {
#if DEB      
        if (k == SPECJAL)
        {
            cout<<"Entering 3"<<endl;
        }
#endif   
        s->left = rotateL(s->left);  
        return rotateR(s);
    }  

    if (curB < -1 && k < rightKey)  
    {  
#if DEB
        if (k == SPECJAL)
        {
            cout<<"Entering 4"<<endl;
        }
#endif   
        s->right = rotateR(s->right);  
        return rotateL(s);
    }

    return s;
}

template<typename Key, typename Info>
void AVL<Key, Info>::printNode(const Node* n) const
{
    cout<<n->k<<"(h:"<<n->height<<")";
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
        cout<<"  |  ";
    }
    printNode(n);

    cout<<endl;
    if (n->left)
    {
        printRECURSION(n->left, h + 1);
    }
}

template<typename Key, typename Info>
typename AVL<Key, Info>::Node* AVL<Key, Info>::minFromRECURSION(Node* s)
{
    if (!s->left) return s;

    return minFromRECURSION(s->left);
}


template<typename Key, typename Info>
typename AVL<Key, Info>::Node* AVL<Key, Info>::removeRECURSION(Node* s, Node* prev, bool lastTimeWentLeft, const Key& k)
{
    if (!s) return s;

    int SPECJAL = 7;

    if (k > s->k)
    {
        removeRECURSION(s->right, s, 0, k);
    }
    else if (k < s->k)
    {
        removeRECURSION(s->left, s, 1, k);
    }

    else if (s->left == 0 && s->right == 0)
    {
        delete s;
        if (lastTimeWentLeft)
        {
            prev->left = 0;
        }
        else
        {
            prev->right = 0;
        }

    }

    else if (s->left == 0)
    {
        s->k = s->right->k;
        s->i = s->right->i;

        delete s->right;
        s->right = 0;
    }
    else if (s->right == 0)
    {
        
        s->k = s->left->k;
        s->i = s->left->i;

        delete s->left;
        s->left = 0;
    }

    
    else
    {
        
        auto minn = minFromRECURSION(s->right);
        s->k = minn->k;
        s->i = minn->i;
        removeRECURSION(s->right, s, 0, minn->k);
    }
        
    updateHeight(s);

    int b = balance(s);

#if 0    
    if (k == SPECJAL)
    {
        cout<<"IMHEREEE!!"<<s->k<<endl;
        print();
    }
#endif

    if (b < -1)
    {
        if (balance(s->left) >= 0)
        {
            return rotateR(s);
        }
        else
        {
            s->left = rotateL(root->left);
            return rotateR(s);
            
        }
    }

    if (b > 1)
    {
        if (balance(s->right) <=  0)
        {
            return rotateL(s);
        }
        else
        {
            s->right = rotateR(s->right);
            return rotateL(s);
        }
    }

    return s;

}

template<typename Key, typename Info>
void AVL<Key, Info>::insert(const Key& k, const Info& i)
{
root =     insertRECURSION(false, k, i, root, root);
}

template<typename Key, typename Info>
void AVL<Key, Info>::print()
{
    if (root)
    {
        printRECURSION(root, 0);
    }
    cout<<endl;
}

template<typename Key, typename Info>
void AVL<Key, Info>::remove(const Key& k)
{
    root = removeRECURSION(root, root, 0, k);
}
