#include <iostream>
#include "avl.h"

using namespace std;


int main()
{
    AVL<int, string> a;

    a.insert(2, "aaa");
    a.print();
    
    
    return 0;
}
