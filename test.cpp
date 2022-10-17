#include "doubly_linkedlist.cpp"
#include <iostream>

using namespace std;

int main(){
    LinkedList<int> list = {1,2,3,4,5};
    LinkedList<int> list1 = {1,2,3,4,5};
    list.Print();
    list1.Print();
    cout<<list.getSize()<<endl;
    list.AddLast(5);
    list.Print();
    cout<<list.getSize()<<endl;
    list.RemoveLast();
    list.Print();
    cout<<list.getSize()<<endl;

    list.At(5, 2);//FIXME
    list.Print();

    list.RemoveAt(2);
    list.Print();
    return 0;
}