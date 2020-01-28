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
void AVL<Key, Info>::clear()
{
    clearRECURSION(root);
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
bool AVL<Key, Info>::findKey(const Key& k)
{
    return findKeyRECURSIVE(root, k);
}
    
template<typename Key, typename Info>
int AVL<Key, Info>::balance(AVL<Key, Info>::Node* s)
{
    if (!s) return 0;
    
    int LH = 0;
    int RH = 0;
    if (s->left) LH = s->left->height;
    if (s->right) RH = s->right->height;

    return  (RH - LH);
}


template<typename Key, typename Info>
int AVL<Key, Info>::heightOfSubtree(AVL<Key, Info>::Node* s)
{
    if (s) return s->height;
    return 0;
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
        if (lastTimeGoneLeft)
        {
            prev->left = new Node(k, i);
            return;
        }
        else
        {
            prev->right = new Node(k, i);
            return;
        }
    }

    updateHeight(s);
    int curB = balance(s); 

    int leftKey = 100000, rightKey = leftKey;
    if (s->left) leftKey = s->left->k;
    if (s->right) rightKey = s->right->k;

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
        cout<<" | ";
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
void AVL<Key, Info>::removeRECURSION(Node* s, Node* prev, bool lastTimeWentLeft, const Key& k)
{
    if (!s) return;

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

    if (b > 1)
    {
        if (balance(s->left) >= 0)
        {
            auto res = rotateR(s);
            if (root == s) root = res;
        }
        else
        {
            s->left = rotateL(root->left);
            auto res = rotateR(s);
            if (root == s) root = res;
        }
    }

    if (b < -1)
    {
        if (balance(s->right) <= 0)
        {
            auto res = rotateL(s);
            if (root == s) root = res;
        }
        else
        {
            s->right = rotateR(s->right);
            auto res = rotateL(s);
            if (root == s) root = res;
        }
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
    cout<<endl;
}

template<typename Key, typename Info>
void AVL<Key, Info>::remove(const Key& k)
{
    removeRECURSION(root, root, 0, k);
}
