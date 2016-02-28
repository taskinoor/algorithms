#ifndef STACK_H_
#define STACK_H_

#include <stdexcept>

class StackFullError : public std::runtime_error {
public:
    StackFullError() : std::runtime_error("Stack is full") {}
};

class StackEmptyError : public std::runtime_error {
public:
    StackEmptyError() : std::runtime_error("Stack is empty") {}
};

#endif
