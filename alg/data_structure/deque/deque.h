#ifndef DEQUE_H_
#define DEQUE_H_

#include <stddef.h>
#include <stdexcept>
#include "list.h"

class DequeEmptyError : public std::runtime_error {
public:
    DequeEmptyError() : std::runtime_error("Deque is empty") {}
};

template <class T>
class Deque {
private:
    LinkedList<T> *list;
    size_t _count;

    Node<T> *get_back_node();
    Node<T> *get_front_node();
public:
    Deque();
    ~Deque();

    void push_back(T);
    void push_front(T);
    T pop_back();
    T pop_front();
    T back();
    T front();
    size_t count();
};

#include "deque.tpp"

#endif
