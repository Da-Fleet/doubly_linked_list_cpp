#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <initializer_list>
#include <memory>
#include <vector>
#include <iostream>

using namespace std;

/**
 * @brief A function definition that handles any amount of parameters of type T and returns an R
 *
 * @return R
 */
template <typename R, typename... T>
using Func = R (*)(T...);

template <class T>
class Node
{
public:
    T data;
    shared_ptr<Node<T>> next;
    weak_ptr<Node<T>> prev;

    /**
     * @brief Construct a new Node object
     *
     * @param data
     */
    Node(T data);

#pragma region Move Semantics

    /**
     * @brief Move Constructor
     *
     * @param other
     */
    Node(Node<T> &&other);

    /**
     * @brief Move Asignment Operator
     *
     * @param other
     * @return Node<T>&
     */
    Node &operator=(Node<T> &&other);

#pragma endregion
};

template <class T>
class LinkedList
{
private:
    shared_ptr<Node<T>> head;
    shared_ptr<Node<T>> tail;
    int size;

public:
#pragma region Constructors and Destructor

    /**
     * @brief Construct a new Linked List object
     * and use a lambda function to initialize the list
     *
     * @param data
     */
    LinkedList(vector<T> data);

    /**
     * @brief Construct a new Linked List< T> object
     *
     */
    LinkedList();

    /**
     * @brief This constructor is a special kind of constructor,
     * called an initializer-list-constructor
     *
     * @param list The list to initialize
     */
    LinkedList(initializer_list<T> list);

#pragma region Move Semantics

    /**
     * @brief Move Constructor
     *
     * @param other
     */
    LinkedList(LinkedList<T> &&other);

    /**
     * @brief Move assignment operator
     *
     * @param other
     * @return LinkedList<T>&
     */
    LinkedList<T> &operator=(LinkedList<T> &&other);

    /**
     * @brief Destroy the Linked List object
     *
     */
    ~LinkedList();

#pragma endregion

#pragma endregion

#pragma region Getters and Setters

    /**
     * @brief Get the Size object
     *
     * @return int
     */
    int length() noexcept(true);

#pragma endregion

#pragma region Public Methods

    /**
     * @brief Add a new node to the end of the list
     *
     * @param data
     */
    void AddLast(T data) noexcept(true);

    /**
     * @brief Remove the last node of the list
     *
     * @return T
     */
    T RemoveLast(); // noexcept(head != nullptr);

    /**
     * @brief Add a new node at the index position
     *
     * @param data
     * @param index
     */
    void At(T data, int index); // noexcept(*this.index >= 0 && *this.index < size);

    /**
     * @brief Removes the node at the index position
     *
     * @param index
     * @return T
     */
    T RemoveAt(int index); // noexcept(*this.index >= 0 && *this.index < size);

    /**
     * @brief
     *
     * @param transformer
     * @return A transformed Linked List
     */
    template <class R>
    LinkedList<R> Map(Func<R, T> map);

    /**
     * @brief Print the list
     *
     */
    void Print();

    /**
     * @brief Print the inverse of the list
     *
     */
    void PrintReverse();

#pragma endregion
};

#endif
