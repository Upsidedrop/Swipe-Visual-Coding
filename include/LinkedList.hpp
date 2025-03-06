template <typename T>
class Node{
public:
    Node(T* p_value)
    :value(p_value), nextNode(nullptr){}
    T* getValue(){
        return value;
    }
    Node* getNextNode(){
        return nextNode;
    }
    void setNextNode(Node* p_nextNode){
        nextNode = p_nextNode;
    }
    void DestroyNode(){
        cout << "deleted node" << endl;
        if(nextNode != nullptr){
            nextNode -> DestroyNode();
        }
        delete value;
        delete this;
    }
private:
    T* value;
    Node* nextNode;
};

template <typename T>
class LinkedList{
public:
    LinkedList(T* p_first){
        firstNode = new Node<T>(p_first);
        lastNode = firstNode;
    }
    ~LinkedList(){
        firstNode -> DestroyNode();
    }
    void Add(T* p_val){
        lastNode -> setNextNode(new Node<T>(p_val));
        lastNode = lastNode -> getNextNode();
    }
    Node<T>* getFirstNode(){
        return firstNode;
    }
private:
    Node<T>* firstNode;
    Node<T>* lastNode;
};