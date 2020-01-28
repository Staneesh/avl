#if !defined(AVL_H)
#define AVL_H

#include <iostream>
using namespace std;


template <typename Key, typename Info>
class AVL
{
    struct Node
    {
        Key k;
        Info i;

        Node* left, *right;
        char balance;

        Node() {left = 0; right = 0; balance = 0;};
        Node(const Key& k_, const Info& i_) {balance = 0; left = 0; right = 0; k = k_; i = i_;};
    };

    Node* root;
    
    void rotateL(Node*);
    void rotateR(Node*);
    void rebalance(Node*);


    void printNode(const Node*) const;
    
    void insertRECURSION(bool lastTimeGoneLeft, const Key& k, const Info& i, Node* s, Node* prev);
    void printRECURSION(Node*);
public:

    AVL();
    ~AVL();
    AVL(const AVL&);

    void insert(const Key&, const Info&);

    void print();
    
};

#include "avl.cpp"

#endif
