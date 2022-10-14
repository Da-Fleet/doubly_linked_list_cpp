// Creating a doubly linked list in C++

template <class T>
class Node{
private:
    T data;
    Node<T> *next;
    Node<T> *prev;
public:
    Node(T data){
        this->data = data;
        this->next = NULL;
        this->prev = NULL;
    }
    T getData(){
        return this->data;
    }
    void setData(T data){
        this->data = data;
    }
    Node<T>* getNext(){
        return this->next;
    }
    void setNext(Node<T> *next){
        this->next = next;
    }
    Node<T>* getPrev(){
        return this->prev;
    }
    void setPrev(Node<T> *prev){
        this->prev = prev;
    }
};

template <class T>
class doubly_linkedlist
{
private:
    Node<int> *head;
    Node<int> *tail;
    int size;
public:
    void Insert(T data){
        Node<T> *newNode = new Node<T>(data);
        if(head == NULL){
            head = newNode;
            tail = newNode;
        }
        else{
            tail->setNext(newNode);
            newNode->setPrev(tail);
            tail = newNode;
        }
        size++;
    }
    
    void InsertAt(int n, T data){
        Node<T> *newNode = new Node<T>(data);
        if(n > size){
            cout << "Invalid Index" << endl;
            return;
        }
        if(n == 0){
            newNode->setNext(head);
            head->setPrev(newNode);
            head = newNode;
        }
        else if(n == size){
            tail->setNext(newNode);
            newNode->setPrev(tail);
            tail = newNode;
        }
        else{
            Node<T> *temp = head;
            for(int i = 0; i < n-1; i++){
                temp = temp->getNext();
            }
            newNode->setNext(temp->getNext());
            temp->getNext()->setPrev(newNode);
            temp->setNext(newNode);
            newNode->setPrev(temp);
        }
        size++;
    }
    
    
    void Push(T data){
        Node<T> *newNode = new Node<T>(data);
        if(head == NULL){
            head = newNode;
            tail = newNode;
        }
        else{
            head->setPrev(newNode);
            newNode->setNext(head);
            head = newNode;
        }
        size++;
    }
    
    void Enqueue(T data){
    Node<T> *newNode = new Node<T>(data);
        if(head == NULL){
            head = newNode;
            tail = newNode;
        }
        else{
            tail->setNext(newNode);
            newNode->setPrev(tail);
            tail = newNode;
        }
        size++;
    
    }
    
    void Delete(T data){
        Node<T> *temp = head;
        while(temp != NULL){
            if(temp->getData() == data){
                if(temp == head){
                    head = head->getNext();
                    head->setPrev(NULL);
                }
                else if(temp == tail){
                    tail = tail->getPrev();
                    tail->setNext(NULL);
                }
                else{
                    temp->getPrev()->setNext(temp->getNext());
                    temp->getNext()->setPrev(temp->getPrev());
                }
                delete temp;
                size--;
                return;
            }
            temp = temp->getNext();
        }
    }
    
    void DeleteAt(int n){
        if(n > size){
            cout << "Invalid Index" << endl;
            return;
        }
        if(n == 0){
            Node<T> *temp = head;
            head = head->getNext();
            head->setPrev(NULL);
            delete temp;
        }
        else if(n == size){
            Node<T> *temp = tail;
            tail = tail->getPrev();
            tail->setNext(NULL);
            delete temp;
        }
        else{
            Node<T> *temp = head;
            for(int i = 0; i < n-1; i++){
                temp = temp->getNext();
            }
            temp->getNext()->getNext()->setPrev(temp);
            temp->setNext(temp->getNext()->getNext());
        }
        size--;
    }
    
    void Dequeue(){
        if(head == NULL){
            return;
        }
        else{
            Node<T> *temp = head;
            head = head->getNext();
            head->setPrev(NULL);
            delete temp;
            size--;
        }
    }
    
    void Pop(){
        if(head == NULL){
            return;
        }
        else{
            Node<T> *temp = tail;
            tail = tail->getPrev();
            tail->setNext(NULL);
            delete temp;
            size--;
        }
    }
    
    T headData(){
        return head->getData();
    }
    
    T tailData(){
        return tail->getData();
    }
    
    int getSize(){
        return size;
    }
    
    
};

doubly_linkedlist::doubly_linkedlist(/* args */)
{
}

doubly_linkedlist::~doubly_linkedlist()
{
}


