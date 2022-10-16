// #include "doubly_linkedlist.h"

// Doble linked list with smart pointers
template <typename T>
class LinkedList {
    struct Node {
        T data;
        shared_ptr<Node> next;
        weak_ptr<Node> prev;
        Node(T data) : data(data) {}
    };
    shared_ptr<Node> head;
    shared_ptr<Node> tail;

public:
    LinkedList() {}
    void add(T data) {
        shared_ptr<Node> node(new Node(data));
        if (head == nullptr) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }
    void print() {
        shared_ptr<Node> node = head;
        while (node != nullptr) {
            cout << node->data << " ";
            node = node->next;
        }
        cout << endl;
    }

    void remove(T data) {
        shared_ptr<Node> node = head;
        while (node != nullptr) {
            if (node->data == data) {
                if (node->prev.lock() != nullptr) {
                    node->prev.lock()->next = node->next;
                } else {
                    head = node->next;
                }
                if (node->next != nullptr) {
                    node->next->prev = node->prev;
                } else {
                    tail = node->prev.lock();
                }
                break;
            }
            node = node->next;
        }
    }

    
};
