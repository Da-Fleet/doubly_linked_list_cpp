#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/**
 * @brief Doubly linked list
 *
 * @tparam T Generic type
 */
template <typename T>
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
        T data;
        Node *next;
        Node *prev;
    };

    Node *head;
    Node *tail;
    int size;

public:
    /**
     * @brief Construct a new Linked List< T> object
     *
     */
    LinkedList<T>();
    void insert(T data);
    void insertAt(int n, T data);
    void remove(int n);
    void print();
    void printReverse();
    int getSize();
};

#endif