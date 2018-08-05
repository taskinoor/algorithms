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
    void push_back(const T& element);
    void push_front(const T& element);

    void pop_back();
    void pop_front();

    T& back();
    const T& back() const;

    T& front();
    const T& front() const;

    std::size_t count() const;

private:
    list::LinkedList<T> list;
    std::size_t count_{0};

    list::Node<T>* back_node();
    const list::Node<T>* back_node() const;

    list::Node<T>* front_node();
    const list::Node<T>* front_node() const;
};

template <class T>
void Deque<T>::push_back(const T& element) {
    list.insert_last(element);
    ++count_;
}

template <class T>
void Deque<T>::push_front(const T& element) {
    list.insert_first(element);
    ++count_;
}

template <class T>
list::Node<T>* Deque<T>::back_node() {
    return const_cast<list::Node<T>*>(
            static_cast<const Deque<T>*>(this)->back_node());
}

template <class T>
const list::Node<T>* Deque<T>::back_node() const {
    const list::Node<T>* node = list.last();

    if (!node) {
        throw except::BufferEmpty();
    }

    return node;
}

template <class T>
list::Node<T>* Deque<T>::front_node() {
    return const_cast<list::Node<T>*>(
            static_cast<const Deque<T>*>(this)->front_node());
}

template <class T>
const list::Node<T>* Deque<T>::front_node() const {
    const list::Node<T>* node = list.first();

    if (!node) {
        throw except::BufferEmpty();
    }

    return node;
}

template <class T>
void Deque<T>::pop_back() {
    list.remove(back_node());
    --count_;
}

template <class T>
void Deque<T>::pop_front() {
    list.remove(front_node());
    --count_;
}

template <class T>
T& Deque<T>::back() {
    return const_cast<T&>(static_cast<const Deque<T>*>(this)->back());
}

template <class T>
const T& Deque<T>::back() const {
    return back_node()->element();
}

template <class T>
T& Deque<T>::front() {
    return const_cast<T&>(static_cast<const Deque<T>*>(this)->front());
}

template <class T>
const T& Deque<T>::front() const {
    return front_node()->element();
}

template <class T>
std::size_t Deque<T>::count() const {
    return count_;
}

}
}

#endif
