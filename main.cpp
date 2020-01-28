#include <iostream>
#include "avl.h"

using namespace std;


int main()
{
    AVL<int, string> a;

    cout<<"FILLING..."<<endl;
    a.insert(1, "a");
    a.insert(2, "b");
    a.insert(3, "c");
    a.insert(5, "d");
    a.insert(4, "e");
    a.insert(7, "f");
    a.insert(6, "g");
    a.insert(8, "h");
    a.print();

    cout<<"REMOVING 6"<<endl;
    a.remove(6);
    a.print();

    cout<<"REMOVING 8"<<endl;
    a.remove(8);
    a.print();

    cout<<"REMOVING 5"<<endl;
    a.remove(5);
    a.print();

    cout<<"REMOVING 7"<<endl;
    a.remove(7);
    a.print();


    cout<<"INSERTING 6"<<endl;
    a.insert(6, "g");
    a.print();

    cout<<"INSERTING 6"<<endl;
    a.insert(6, "g");
    a.print();

    cout<<"REMOVING 3"<<endl;
    a.remove(3);
    a.print();

    cout<<"INSERTING 3"<<endl;
    a.insert(3, "c");
    a.print();

    return 0;
}
