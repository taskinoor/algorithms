#ifndef ALG_STACK_H_
#define ALG_STACK_H_

#include <stddef.h>

#include <stdexcept>

namespace alg {

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
    int _top;
    size_t size;
public:
    Stack(size_t);
    ~Stack();

    void push(T);
    T pop();
    T top();
    size_t count();
};

}

#include "stack.tpp"

#endif
