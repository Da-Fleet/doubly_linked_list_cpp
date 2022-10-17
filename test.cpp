#include "doubly_linkedlist.cpp"
#include <iostream>

using namespace std;

int main(){
    //[ ]: Testing Node Class
    //[ ]: Node default constructor
    //[ ]: Node copy constructor
    //[ ]: Node move constructor
    //[ ]: Testing Linked List Class

    LinkedList<int> test1(vector<int>{1,2,3,4,5});
    test1.Print();
    cout << test1.getSize() << endl;
    LinkedList<int> test2;
    test2.Print();
    cout << test2.getSize() << endl;
    test2.AddLast(10);
    test2.Print();
    cout << test2.getSize() << endl;
    test1.RemoveLast();
    test1.Print();
    cout << test1.getSize() << endl;
    test1.At(3, 1);
    test1.Print();
    cout << test1.getSize() << endl;
    return 0;
}