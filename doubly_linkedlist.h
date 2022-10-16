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
    struct Node
    {
        T data;
        shared_ptr<Node> next;
        weak_ptr<Node> prev;
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
    LinkedList<T>();


    //Move Semantics
    /**
     * @brief Construct a new Linked List< T> object
     *
     * @param other
     */
    LinkedList<T>(LinkedList<T> &&other);

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


    void print();
    void printReverse();
    
    #pragma endregion
};

#endif