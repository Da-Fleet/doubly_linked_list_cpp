# Doubly Linked List in C++

Para la implementación de `LinkedList` se utilizaron los punteros inteligentes

```cpp
template <class T>
class LinkedList
{
private:
    shared_ptr<Node<T>> head;
    shared_ptr<Node<T>> tail;
    int size;

public:
    LinkedList();
    void AddLast(T data);
    T RemoveLast();
    void At(T data, int index);
    T RemoveAt(int index);
    T RemoveData(T data);
    void Print();
};
```

`doubly_linkedlist.h`

```cpp
template <class T>
class Node
{
public:
    T data;
    shared_ptr<Node<T>> next;
    weak_ptr<Node<T>> prev;

    Node(T data);
};
```
