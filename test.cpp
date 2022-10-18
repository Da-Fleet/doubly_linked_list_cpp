#include "doubly_linkedlist.cpp"
#include <iostream>

using namespace std;

int main()
{
    //[ ]: Testing Node Class
    //[x]: Node default constructor
    // Node<int> node(4);
    // Node<int> node1(3);
    // Node<int> node2(2);
    // Node<int> node3(1);
    // cout << node.data << endl;

    //[ ]: Node move constructor
    //[ ]: Testing Linked List Class

    // LinkedList<int> test1(vector<int>{1,2,3,4,5});
    // test1.Print();
    // cout << test1.getSize() << endl;
    // LinkedList<int> test2;
    // test2.Print();
    // cout << test2.getSize() << endl;
    // test2.AddLast(10);
    // test2.Print();
    // cout << test2.getSize() << endl;
    // test1.RemoveLast();
    // test1.Print();
    // cout << test1.getSize() << endl;
    // test1.At(3, 1);
    // test1.Print();
    // cout << test1.getSize() << endl;
    // Node<int> node4 = move(node);
    // cout<<node4.data<<endl;
    // cout<<node.data<<endl;

    //[ ]: Node move asignment operator
    // node4 = move(node1);
    // cout<<node4.data<<endl;
    // cout<<node1.data<<endl;

    //[ ]: Testing Linked List Class
    //[ ]: Linked List default constructor
    // LinkedList<int> list;
    // cout << "Empty Constructor" << endl;
    // list.Print();
    //[ ]: Linked List move constructor

    //[X]: Linked List AddLast
    //[X]: Linked List RemoveLast
    //[X]: Linked List At
    //[X]: Linked List RemoveAt

#pragma region Test LinkedList 1
    LinkedList<int> test1 = { 1, 2, 3, 4, 5, 6 };
    cout << test1.length() << endl;
    test1.At(3, 4);
    cout << test1.length() << endl;
    test1.At(2, 4);
    cout << test1.length() << endl;
    test1.At(2, 0);
    cout << test1.length() << endl;
    test1.At(90, 8);
    cout << test1.length() << endl;
    test1.Print();
    test1.PrintReverse();

    cout << test1.length() << endl;
    test1.RemoveLast();
    cout << test1.length() << endl;
    test1.RemoveLast();
    cout << test1.length() << endl;
    test1.RemoveLast();
    cout << test1.length() << endl;
    test1.RemoveLast();
    cout << test1.length() << endl;
    test1.Print();
    test1.PrintReverse();

    cout << test1.length() << endl;
    test1.RemoveAt(0);
    cout << test1.length() << endl;
    test1.RemoveAt(2);
    cout << test1.length() << endl;
    test1.RemoveAt(3);
    cout << test1.length() << endl;
    test1.RemoveAt(0);
    cout << test1.length() << endl;
    test1.Print();
    test1.PrintReverse();

#pragma endregion

#pragma region Test LinkedList2

LinkedList<string> names = {};
cout<< names.length() << endl;
names.AddLast("Aldair");
names.At("Glenda", 0);
cout<< names.length() << endl;
names.Print();
names.PrintReverse();

names.AddLast("Yero");
names.At("Mauro", 2);
names.AddLast("Leismael");
cout<< names.length() << endl;
names.Print();
names.PrintReverse();

names.RemoveLast();
names.RemoveAt(0);
cout<< names.length() << endl;
names.Print();
names.PrintReverse();

#pragma endregion
    return 0;
}