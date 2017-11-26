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

template <class T>
Stack<T>::Stack(std::size_t n) {
    size = n;
    top_ = -1;
    buffer = new T[n];
}

template <class T>
Stack<T>::~Stack() {
    delete[] buffer;
}

template <class T>
void Stack<T>::push(T element) {
    if (top_ == size - 1) {
        throw StackFullError();
    }

    top_++;
    buffer[top_] = element;
}

template <class T>
T Stack<T>::pop() {
    if (top_ == -1) {
        throw StackEmptyError();
    }

    top_--;
    return buffer[top_ + 1];
}

template <class T>
T Stack<T>::top() {
    if (top_ == -1) {
        throw StackEmptyError();
    }

    return buffer[top_];
}

template <class T>
std::size_t Stack<T>::count() {
    return top_ + 1;
}

}

#endif
