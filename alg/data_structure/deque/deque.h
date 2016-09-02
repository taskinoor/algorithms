#ifndef ALG_DEQUE_H_
#define ALG_DEQUE_H_

#include <cstddef>
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
    std::size_t count_;

    ListNode<T> *back_node();
    ListNode<T> *front_node();

public:
    Deque();
    virtual ~Deque();

    void push_back(T element);
    void push_front(T element);

    T pop_back();
    T pop_front();

    T back();
    T front();

    std::size_t count();
};

}

#include "deque.tpp"

#endif
