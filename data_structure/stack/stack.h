#ifndef STACK_H_
#define STACK_H_

#include <stddef.h>

#include <stdexcept>

class StackFullError : public std::runtime_error {
public:
    StackFullError() : std::runtime_error("Stack is full") {}
};

class StackEmptyError : public std::runtime_error {
public:
    StackEmptyError() : std::runtime_error("Stack is empty") {}
};

template <class T>
class Stack {
private:
    T *buffer;
    int top;
    size_t size;
public:
    Stack(size_t);
    ~Stack();
    void push(T);
    T pop();
};

#include "stack.tpp"

#endif
