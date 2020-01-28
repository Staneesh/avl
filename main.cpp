#include <iostream>
#include "avl.h"

using namespace std;


int main()
{
    AVL<int, string> a;

    a.insert(1, "a");
    a.insert(2, "b");
    a.insert(3, "c");
    a.insert(5, "d");
    a.insert(4, "e");
    a.insert(7, "f");
    a.insert(6, "g");
    a.insert(8, "h");
    
    a.print();
    
    
    return 0;
}
