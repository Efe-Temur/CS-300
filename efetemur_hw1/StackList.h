#ifndef STACKLIST_H
#define STACKLIST_H

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include<cstdlib>
#include <random>
#include <iostream>

template<typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
    };

    Node* top;
    int size;

public:
    Stack() : top(nullptr), size(0) {}
    ~Stack();

    void push(T value);
    void pop();
    T& peek() ;
    int getSize() const;
    bool isEmpty() const;
    void clear();
};

//destructor
template<typename T>
Stack<T>::~Stack() {
    while (top != nullptr) {
        Node* temp = top;
        top = top->next;
        delete temp;
    }
}

template<typename T>
void Stack<T>::push(T value) {
    Node* newNode = new Node{ value, top };
    top = newNode;
    size++;
}

template<typename T>
void Stack<T>::pop() {
    if (isEmpty()) {
        throw std::out_of_range("Stack is empty");
    }
    Node* temp = top;
    top = top->next;
    delete temp;
    size--;
}

template<typename T>
T& Stack<T>::peek() {
    if (isEmpty()) {
        throw std::out_of_range("Stack is empty");
    }
    return top->data;
}

template<typename T>
int Stack<T>::getSize() const {
    return size;
}

template<typename T>
bool Stack<T>::isEmpty() const {
    return top == nullptr;
}

template<typename T>
void Stack<T>::clear() {
    while (top != nullptr) {
        Node* temp = top;
        top = top->next;
        delete temp;
    }
    size = 0;
}


#endif STACKLIST_H