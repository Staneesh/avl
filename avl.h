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
        ~Node() {};
        Node(const Key& k_, const Info& i_) {height = 1; left = 0; right = 0; k = k_; i = i_;};
    };

    Node* root;
    
    Node* rotateL(Node*);
    Node* rotateR(Node*);
    void updateHeight(Node* s);
    int balance(const Node* s) const;

    void printNode(const Node*) const;
    
    Node* insertRECURSION(bool lastTimeGoneLeft, const Key& k, const Info& i, Node* s, Node* prev);
    void printRECURSION(Node*, int h);
    Node* removeRECURSION(Node* s, Node* prev, bool, const Key& k);
    void clearRECURSION(Node* s);
    int heightOfSubtree(const Node* s) const;
    bool findKeyRECURSIVE(Node* s, const Key& k);
    Node* minFromRECURSION(Node* s);
    void updateRECURSION(Node* s, const Key&, const Info&);

    
public:
    AVL(){root = 0;}
    ~AVL();

    void update(const Key&, const Info&);
    void insert(const Key&, const Info&);
    void remove(const Key&);
    void print();
    void clear();
    bool checkKey(const Key& k);
};

#include "avl.cpp"

#endif
