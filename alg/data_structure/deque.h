#ifndef ALG_DEQUE_H_
#define ALG_DEQUE_H_

#include <cstddef>
#include <stdexcept>

#include "alg/data_structure/list.h"

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

template <class T>
Deque<T>::Deque() {
    list = new LinkedList<T>();
    count_ = 0;
}

template <class T>
Deque<T>::~Deque() {
    delete list;
}

template <class T>
void Deque<T>::push_back(T element) {
    list->insert_last(element);
    count_++;
}

template <class T>
void Deque<T>::push_front(T element) {
    list->insert_first(element);
    count_++;
}

template <class T>
ListNode<T> *Deque<T>::back_node() {
    ListNode<T> *node = list->last();

    if (!node) {
        throw DequeEmptyError();
    }

    return node;
}

template <class T>
ListNode<T> *Deque<T>::front_node() {
    ListNode<T> *node = list->first();

    if (!node) {
        throw DequeEmptyError();
    }

    return node;
}

template <class T>
T Deque<T>::pop_back() {
    ListNode<T> *node = back_node();
    T element = node->element();

    list->remove(node);
    count_--;

    return element;
}

template <class T>
T Deque<T>::pop_front() {
    ListNode<T> *node = front_node();
    T element = node->element();

    list->remove(node);
    count_--;

    return element;
}

template <class T>
T Deque<T>::back() {
    return back_node()->element();
}

template <class T>
T Deque<T>::front() {
    return front_node()->element();
}

template <class T>
std::size_t Deque<T>::count() {
    return count_;
}

}

#endif