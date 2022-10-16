#include "doubly_linkedlist.h"

template <typename T>
LinkedList<T>::LinkedList()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template <typename T>
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

template <typename T>
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

template <typename T>
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