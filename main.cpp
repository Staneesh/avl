#include <iostream>
#include "avl.h"

using namespace std;


int main()
{
    AVL<int, string> a;


    for (int i = 15; i >= 1; i--)
    {
        cout<<"Inserting "<<i<<endl;
        a.insert(i, "a");
        a.print();
    
    }


    for (int i = 5; i <= 10; i++)
    {
        cout<<"Removing "<<i<<endl;
        a.remove(i);
        a.print();
        
    }
    
    return 0;
}
