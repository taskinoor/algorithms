#ifndef ALG_DEQUE_H_
#define ALG_DEQUE_H_

#include <stddef.h>
#include <stdexcept>

#include "list.h"

namespace alg {

class DequeEmptyError : public std::runtime_error {
public:
    DequeEmptyError() : std::runtime_error("Deque is empty") {}
};

template <class T>
class Deque {
private:
    LinkedList<T> *list;
    size_t _count;

    ListNode<T> *get_back_node();
    ListNode<T> *get_front_node();
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

}

#include "deque.tpp"

#endif
