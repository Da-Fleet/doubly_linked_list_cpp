#include "doubly_linkedlist.h"

#pragma region Constructors and Destructors Implementations

template <typename T>
LinkedList<T>::LinkedList()
{
    cout<<"Default constructor called"<<endl;
    head = nullptr;
    tail = nullptr;
    size = 0;
}

// Copy Semantics
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &other)
{
    cout<<"Copy constructor called"<<endl;
    swap(head, other.head);
    swap(tail, other.tail);
    swap(size, other.size);
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &other)
{
    cout<<"Copy assignment operator called"<<endl;
    swap(*this, other);
    return *this;
}

// Move Semantics
template <typename T>
LinkedList<T>::LinkedList(LinkedList<T> &&other)
{
    cout<<"Move constructor called"<<endl;
    swap(head, other.head);
    swap(tail, other.tail);
    swap(size, other.size);
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(LinkedList<T> &&other)
{
    cout<<"Move assignment operator called"<<endl;
    swap(*this, other);
    return *this;
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

template <typename T>
void LinkedList<T>::AddLast(T data) noexcept(true)
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

template <typename T>
T LinkedList<T>::RemoveLast() noexcept(head != nullptr)
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

template <typename T>
void LinkedList<T>::At(T data, int index) noexcept(index = > 0 && index < size)
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    else
    {
        shared_ptr<Node> node = head;
        for (int i = 0; i < index; i++)
        {
            node = node->next;
        }
        node->data = data;
    }
}

template <typename T>
T LinkedList<T>::RemoveAt(int index) noexcept(index = > 0 && index < size)
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    else
    {
        shared_ptr<Node> node = head;
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

#pragma endregion