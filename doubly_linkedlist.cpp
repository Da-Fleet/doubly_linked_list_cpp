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
class Doubly_linkedlist
{
private:
    Node<int> *head;
    Node<int> *tail;
    int size;
public:

#pragma region Add Methods
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
#pragma endregion

#pragma region Removing Methods
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
#pragma endregion

#pragma region Properties Methods
    T headData(){
        return head->getData();
    }
    
    T tailData(){
        return tail->getData();
    }
    
    int getSize(){
        return size;
    }
#pragma endregion   

#pragma region Seeker Methods
    bool Search(T data){
        Node<T> *temp = head;
        while(temp != NULL){
            if(temp->getData() == data){
                return true;
            }
            temp = temp->getNext();
        }
        return false;
    }
    
    int IndexOf(T data){
        Node<T> *temp = head;
        int index = 0;
        while(temp != NULL){
            if(temp->getData() == data){
                return index;
            }
            temp = temp->getNext();
            index++;
        }
        return -1;
    }
#pragma endregion

#pragma region Get Methods
    T Get(int n){
        if(n > size){
            cout << "Invalid Index" << endl;
            return -1;
        }
        Node<T> *temp = head;
        for(int i = 0; i < n; i++){
            temp = temp->getNext();
        }
        return temp->getData();
    }
#pragma endregion

#pragma region Set Methods
    void Set(int n, T data){
        if(n > size){
            cout << "Invalid Index" << endl;
            return;
        }
        Node<T> *temp = head;
        for(int i = 0; i < n; i++){
            temp = temp->getNext();
        }
        temp->setData(data);
    }
#pragma endregion
};

template <class T>
Doubly_linkedlist::Doubly_linkedlist(T* data, int size){
    for(int i = 0; i < size; i++){
        Insert(data[i]);
    }
}

template <class T>
Doubly_linkedlist::~Doubly_linkedlist()
{
   head = NULL;
   tail = NULL;
   size = 0;
}


