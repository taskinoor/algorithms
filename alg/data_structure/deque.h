#ifndef ALG_DS_DEQUE_H_
#define ALG_DS_DEQUE_H_

#include <cstddef>

#include "alg/common/exception.h"
#include "alg/data_structure/linked_list.h"

namespace alg {
namespace ds {

template <class T>
class Deque {
public:
    Deque();
    ~Deque();

    void push_back(T element);
    void push_front(T element);

    T pop_back();
    T pop_front();

    T back();
    T front();

    std::size_t count();

private:
    list::LinkedList<T>* list;
    std::size_t count_;

    list::Node<T>* back_node();
    list::Node<T>* front_node();
};

template <class T>
Deque<T>::Deque() {
    list = new list::LinkedList<T>();
    count_ = 0;
}

template <class T>
Deque<T>::~Deque() {
    delete list;
}

template <class T>
void Deque<T>::push_back(T element) {
    list->insert_last(element);
    ++count_;
}

template <class T>
void Deque<T>::push_front(T element) {
    list->insert_first(element);
    ++count_;
}

template <class T>
list::Node<T>* Deque<T>::back_node() {
    list::Node<T>* node = list->last();

    if (!node) {
        throw except::BufferEmpty();
    }

    return node;
}

template <class T>
list::Node<T>* Deque<T>::front_node() {
    list::Node<T>* node = list->first();

    if (!node) {
        throw except::BufferEmpty();
    }

    return node;
}

template <class T>
T Deque<T>::pop_back() {
    list::Node<T>* node = back_node();
    T element = node->element();

    list->remove(node);
    --count_;

    return element;
}

template <class T>
T Deque<T>::pop_front() {
    list::Node<T>* node = front_node();
    T element = node->element();

    list->remove(node);
    --count_;

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
}

#endif
