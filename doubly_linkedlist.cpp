#include "doubly_linkedlist.h"

using namespace std;

#pragma region Constructors and Destructors Implementations

template <class T>
Node<T>::Node(T data) : data(data) {}

template <class T>
LinkedList<T>::LinkedList()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template <class T>
LinkedList<T>::LinkedList(initializer_list<T> list)
{
    for (auto it = list.begin(); it != list.end(); it++)
    {
        this->AddLast(*it);
    }
}

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

template <typename T>
int LinkedList<T>::getSize() noexcept(true)
{
    return size;
}

#pragma endregion

#pragma region Public Methods Implementations

template <class T>
void LinkedList<T>::AddLast(T data) noexcept(true)
{
    shared_ptr<Node<T>> node(new Node<T>(data));
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

template <class T>
T LinkedList<T>::RemoveLast() noexcept(*this.head != nullptr)
{
    if (head == nullptr)
    {
        throw std::out_of_range("List is empty");
    }
    else
    {
        T data = tail->data;
        tail = tail->prev.lock();
        if (tail == nullptr)
        {
            head = nullptr;
        }
        else
        {
            tail->next = nullptr;
        }
        size--;
        return data;
    }
}

template <class T>
void LinkedList<T>::At(T data, int index) noexcept(*this.index >= 0 && *this.index < size)
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    else
    {
        shared_ptr<Node<T>> node = head;
        for (int i = 0; i < index; i++)
        {
            node = node->next;
        }
        node->data = data;
    }
}

template <class T>
T LinkedList<T>::RemoveAt(int index) noexcept(*this.index >=  0 && *this.index < size)
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    else
    {
        shared_ptr<Node<T>> node = head;
        for (int i = 0; i < index; i++)
        {
            node = node->next;
        }
        T data = node->data;
        if (node == head)
        {
            head = node->next;
        }
        else
        {
            node->prev.lock()->next = node->next;
        }
        if (node == tail)
        {
            tail = node->prev.lock();
        }
        else
        {
            node->next->prev = node->prev;
        }
        size--;
        return data;
    }
}

template <class T>
void LinkedList<T>::Print()
{
    shared_ptr<Node<T>> node = head;
    while (node != nullptr)
    {
        cout << node->data << " ";
        node = node->next;
    }
    cout << endl;
}

#pragma endregion