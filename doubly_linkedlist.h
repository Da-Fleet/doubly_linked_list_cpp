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

    //Copy Semmantics

    /**
     * @brief Copy constructor
     *
     * @param other
     */
    LinkedList<T>(const LinkedList<T>& other);

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
    LinkedList<T>(LinkedList<T> &&other);

    /**
     * @brief Move assignment operator
     * 
     * @param other 
     * @return LinkedList<T>& 
     */
    LinkedList<T>& operator=(LinkedList<T> &&other);

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
     * @brief Remove the last node of the list
     * 
     * @return T 
     */
    T RemoveLast();

    /**
     * @brief Add a new node at the index position
     * 
     * @param data 
     * @param index 
     */
    void At(T data, int index);

    /**
     * @brief Removes the node at the index position
     * 
     * @param index 
     * @return T 
     */
    T RemoveAt(int index);

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