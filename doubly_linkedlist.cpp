#include "doubly_linkedlist.h"

using namespace std;

template <class T>
Node<T>::Node(T data) : data(data)
{
    cout<<"Node default constructor called"<<endl;
}

template <class T>
Node<T>::Node(Node<T> &other)
{
    cout<<"Node copy constructor called"<<endl;
    //Deep Copy
    this->data = other.data;
    this->next = other.next;
    this->prev = other.prev;
}

template <class T>
Node<T> &Node<T>::operator=(Node<T> &other)
{
    cout<<"Node copy operator called"<<endl;
    //Deep Copy
    this->data = other.data;
    this->next = other.next;
    this->prev = other.prev;
    return *this;
}

template <class T>
Node<T>::Node(Node<T> &&other)noexcept
{
    cout<<"Node move constructor called"<<endl;
    //Checking for self assignment
    if (this != &other)
    {
        //Move data
        this->data = other.data;
        this->next = other.next;
        this->prev = other.prev;

        //Delete other
        other.data = T();
        other.next = nullptr;
        other.prev.lock() = nullptr;
    }
}

template <class T>
Node<T> &Node<T>::operator=(Node<T> &&other)noexcept
{
    cout<<"Node move operator called"<<endl;
    // checking for self assignment
    if (this != &other)
    {
        data = other.data;
        next = other.next;
        prev = other.prev;
        other.data = T();
        other.next = nullptr;
        other.prev.lock = nullptr;
    }
    return *this;
}

template <class T>
LinkedList<T>::LinkedList()
{
    cout<<"LinkedList default constructor called"<<endl;
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template <class T>
LinkedList<T>::LinkedList(initializer_list<T> list)
{
    size = 0;
    for (auto it = list.begin(); it != list.end(); it++)
    {
        this->AddLast(*it);
    }
}

template <class T>
LinkedList<T>::LinkedList(LinkedList<T> &other)
{
    cout<<"LinkedList copy constructor called"<<endl;
    //Deep Copy
    head = other.head;
    tail = other.tail;
    size = other.size;
}

template <class T>
LinkedList<T> &LinkedList<T>::operator=(LinkedList<T> &other)
{
    cout<<"LinkedList copy operator called"<<endl;
    //Deep Copy
    head = other.head;
    tail = other.tail;
    size = other.size;
    return *this;
}

template <class T>
LinkedList<T>::LinkedList(LinkedList<T> &&other)
{
    cout<<"LinkedList move constructor called"<<endl;
    swap(head, other.head);
    swap(tail, other.tail);
    swap(size, other.size);
}

template <class T>
LinkedList<T> &LinkedList<T>::operator=(LinkedList<T> &&other)
{
    // checking if the object is not being assigned to itself
    if (this != &other)
    {
        head = other.head;
        tail = other.tail;
        size = other.size;
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }
    return *this;
}

#pragma region ctor and dtor

template <class T>
LinkedList<T>::LinkedList(vector<T> data)
{
    size = 0;
    for_each(data.begin(), data.end(), [&](T &item)
             { this->AddLast(item); });
}

template <class T>
LinkedList<T>::~LinkedList()
{
    head.delete();
    tail.delete();
}
#pragma endregion

#pragma region Getters and Setters Implementations

template <class T>
int LinkedList<T>::length() noexcept(true)
{
    return size;
}

#pragma endregion

#pragma region Public Methods Implementations

template <class T>
void LinkedList<T>::AddLast(T data) noexcept(true)
{
    shared node(new Node<T>(data));
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
    size++;
}

template <class T>
T LinkedList<T>::RemoveLast() // noexcept(head != nullptr)
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
void LinkedList<T>::At(T data, int index) // noexcept(*this.index >= 0 && *this.index < size)
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    else
    {
        shared node = head;
        for (int i = 0; i < index; i++)
        {
            node = node->next;
        }
        shared newNode(new Node<T>(data));
        if (index == 0)
        {
            if (size != 0)
            {
                node->prev = newNode;
                newNode->next = node;
            }
            head = newNode;
        }
        else if (0 <= index && index < size - 1)
        {
            node->prev.lock()->next = newNode;
            newNode->prev = node->prev;
            node->prev = newNode;
            newNode->next = node;
        }
        else {
            newNode->prev = node;
            node->next = newNode;
            tail = newNode;
        }
        size++;
    }
}

template <class T>
T LinkedList<T>::RemoveAt(int index) // znoexcept(*this.index >= 0 && *this.index < size)
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    else
    {
        shared node = head;
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
template <class R>
LinkedList<R> LinkedList<T>::Map(Func<R, T> map) // noexcept(true)
{
    LinkedList<R> result;
    shared node = head;
    while (node != nullptr)
    {
        result.AddLast(transformer(node->data));
        node = node->next;
    }
    return result;
}

template <class T>
void LinkedList<T>::Print()
{
    shared node = head;
    while (node != nullptr)
    {
        cout << node->data << " ";
        node = node->next;
    }
    cout << endl;
}

template <class T>
void LinkedList<T>::PrintReverse()
{
    shared node = tail;
    while (node != nullptr)
    {
        cout << node->data << " ";
        node = node->prev.lock();
    }
    cout << endl;
}

#pragma endregion