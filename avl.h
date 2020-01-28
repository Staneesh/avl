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
        int height;

        Node() {left = 0; right = 0; height = 0;};
        Node(const Key& k_, const Info& i_) {height = 0; left = 0; right = 0; k = k_; i = i_;};
    };

    Node* root;
    
    Node* rotateL(Node*);
    Node* rotateR(Node*);
    void rebalance(Node*);

    void updateHeight(Node* s);
    void printNode(const Node*) const;
    
    void insertRECURSION(bool lastTimeGoneLeft, const Key& k, const Info& i, Node* s, Node* prev);
    void printRECURSION(Node*, int h);
public:
    AVL(){root = 0;}

    void insert(const Key&, const Info&);

    void print();
    
};

#include "avl.cpp"

#endif
