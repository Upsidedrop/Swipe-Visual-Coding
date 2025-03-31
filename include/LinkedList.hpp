#pragma once

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
    ~LinkedList(){
        firstNode -> DestroyNode();
    }
    void Add(T* p_val){
        if(firstNode == nullptr){
            firstNode = new Node<T>(p_val);
            lastNode = firstNode;
            return;
        }
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