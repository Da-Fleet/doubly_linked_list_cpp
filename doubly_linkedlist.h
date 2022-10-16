#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <initializer_list>
#include <memory>
#include <iostream>

using namespace std;

/**
 * @brief Doubly linked list
 *
 * @tparam T Generic type
 */
template <class T>
class LinkedList
{
private:
    /**
     * @brief Node class
     *
     * @tparam T
     */
    class Node
    {
        public:
            T data;
            shared_ptr<Node> next;
            weak_ptr<Node> prev;
            Node(T data);
    };

    shared_ptr<Node> head;
    shared_ptr<Node> tail;
    int size;

public:

    #pragma region Constructors and Destructor
    
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

    /**
     * @brief Copy constructor
     *
     * @param other Other list
     */
    LinkedList(const LinkedList<T>& other);

    /**
     * @brief Copy assignment operator
     *
     * @param other
     * @return LinkedList<T>&
     */
    LinkedList<T>& operator=(const LinkedList<T>& other);

    //Move Semantics
    /**
     * @brief Construct a new Linked List< T> object
     *
     * @param other
     */
    LinkedList(LinkedList<T> &&other);

    #pragma endregion

    #pragma region Getters and Setters

    /**
     * @brief Get the Size object
     *
     * @return int
     */
    int getSize();

    #pragma endregion

    #pragma region Public Methods
    
    /**
     * @brief Add a new node to the end of the list
     *
     * @param data
     */
    void AddLast(T data);

    /**
     * @brief Removes the last node of the list
     * 
     * @param n 
     */
    void RemoveLast(int n);

    /**
     * @brief 
     * 
     * @param data 
     * @return T 
     */
    T RemoveData(T data);
    void Print();
    void PrintReverse();
    
    #pragma endregion
};

#endif