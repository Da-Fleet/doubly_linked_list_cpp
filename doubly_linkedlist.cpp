#include "doubly_linkedlist.h"

using namespace std;

#pragma region Constructors and Destructors Implementations

template <class T>
LinkedList<T>::LinkedList()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template<class T>
LinkedList<T>::LinkedList(std::initializer_list<T> list)
{
    for (auto it = list.begin(); it != list.end(); it++)
    {
        this->AddLast(*it);
    }
}

// Copy Semantics
template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> &other)
{
    // swap(head, other.head);
    // swap(tail, other.tail);
    // swap(size, other.size);

    //TODO: Fix me!!!! 
}

template <class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &other)
{
    // swap(*this, other);
    // return *this;
    //TODO: Fix me!!!!
}

#pragma endregion

#pragma region Getters and Setters Implementations

#pragma endregion

#pragma region Public Methods Implementations

template <class T>
T LinkedList<T>::RemoveData(T data)
{
    shared_ptr<Node> node = head;
    while (node != nullptr)
    {
        if (node->data == data)
        {
            if (node->prev.lock() != nullptr)
            {
                node->prev.lock()->next = node->next;
            }
            else
            {
                head = node->next;
            }
            if (node->next != nullptr)
            {
                node->next->prev = node->prev;
            }
            else
            {
                tail = node->prev.lock();
            }
            break;
        }
        node = node->next;
    }
}

template <class T>
void LinkedList<T>::Print()
{
    shared_ptr<Node> node = head;
    while (node != nullptr)
    {
        cout << node->data << " ";
        node = node->next;
    }
    cout << endl;
}

template <class T>
void LinkedList<T>::AddLast(T data)
{
    shared_ptr<Node> node(new Node(data));
    if (head == nullptr)
    {
        head = node;
        tail = node;
    }
    else
    {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
}

#pragma endregion