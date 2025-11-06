#pragma once

#include <iostream>

template<typename T>
class RandomDeletionStack{
    public:
    RandomDeletionStack(T p_value): value(p_value), child(nullptr), last(this){}
    void FullKill(){
        if(child != nullptr){
            child -> FullKill();
        }
        delete this;
    }
    void Push(T p_item){
        last -> SetChild(new RandomDeletionStack<T>(p_item));
        last = last -> GetChild();
    }
    RandomDeletionStack<T>* DeleteElement(T p_item){
        if(child -> GetValue() == p_item){
            bool wasLast = child -> GetChild() == nullptr;
            SpliceChild();
            return wasLast? this : nullptr;
        }
        if(child == nullptr){
            return nullptr;
        }
        return child -> DeleteElement(p_item);
    }
    void SetLast(RandomDeletionStack<T>* p_last){
        last = p_last;
    }
    void SpliceChild(){
        auto oldChild = child;
        child = child -> GetChild();
        delete oldChild;
    }
    void SetChild(RandomDeletionStack<T>* p_child){
        child = p_child;
    }
    RandomDeletionStack<T>* GetChild(){
        return child;
    }
    T GetValue(){
        return value;
    }
    private:
    RandomDeletionStack<T>* last;
    RandomDeletionStack<T>* child;
    T value;
};
