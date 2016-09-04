#ifndef ALG_STACK_H_
#define ALG_STACK_H_

#include <cstddef>
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
    int top_;
    std::size_t size;

public:
    Stack(std::size_t n);
    virtual ~Stack();

    void push(T element);
    T pop();
    T top();
    std::size_t count();
};

}

#include "stack.tpp"

#endif
