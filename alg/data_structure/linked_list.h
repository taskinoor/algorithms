#ifndef ALG_DS_LIST_LINKED_LIST_H_
#define ALG_DS_LIST_LINKED_LIST_H_

#include "alg/common/iterator.h"

namespace alg {
namespace ds {
namespace list {

template <class T> class LinkedList;
template <class T> class Iterator;

template <class T>
class Node {
public:
    explicit Node(const T& element = T());

    T& element();
    const T& element() const;

private:
    Node<T>* next{nullptr};
    Node<T>* prev{nullptr};

    T element_;

    friend class LinkedList<T>;
};

template <class T>
class LinkedList {
public:
    LinkedList();
    ~LinkedList();

    Node<T>* first();
    Node<T>* last();
    Node<T>* after(Node<T>* p);
    Node<T>* before(Node<T>* p);

    void insert_after(Node<T>* p, T element);
    void insert_before(Node<T>* p, T element);
    void insert_first(T element);
    void insert_last(T element);

    Node<T>* search(T element);
    void remove(Node<T>* p);

    Iterator<T>* create_iterator(bool forward = true);
    void destroy_iterator(Iterator<T>* iter);

private:
    Node<T>* head;
    Node<T>* tail;
};

template <class T>
class Iterator : public patterns::Iterator<T> {
public:
    Iterator(LinkedList<T>* list);
    virtual ~Iterator() {}

    virtual bool is_done() const;
    virtual T current_item() const;

protected:
    LinkedList<T>* list;
    Node<T>* current;
};

template <class T>
class ForwardIterator : public Iterator<T> {
public:
    ForwardIterator(LinkedList<T>* list) : Iterator<T>(list) {}

    void first();
    void next();
};

template <class T>
class BackwardIterator : public Iterator<T> {
public:
    BackwardIterator(LinkedList<T>* list) : Iterator<T>(list) {}

    void first();
    void next();
};

template <class T>
Node<T>::Node(const T& element) : element_{element} {}

template <class T>
T& Node<T>::element() {
    return element_;
}

template <class T>
const T& Node<T>::element() const {
    return element_;
}

template <class T>
LinkedList<T>::LinkedList() : head{new Node<T>}, tail{new Node<T>} {
    head->next = tail;
    tail->prev = head;
}

template <class T>
LinkedList<T>::~LinkedList() {
    Node<T>* current = head->next;

    while (current != tail) {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }

    delete head;
    delete tail;
}

template <class T>
Node<T>* LinkedList<T>::first() {
    return after(head);
}

template <class T>
Node<T>* LinkedList<T>::last() {
    return before(tail);
}

template <class T>
Node<T>* LinkedList<T>::after(Node<T>* p) {
    if (p->next == tail) {
        return nullptr;
    }

    return p->next;
}

template <class T>
Node<T>* LinkedList<T>::before(Node<T>* p) {
    if (p->prev == head) {
        return nullptr;
    }

    return p->prev;
}

template <class T>
void LinkedList<T>::insert_after(Node<T>* p, T element) {
    Node<T>* node = new Node<T>(element);

    node->next = p->next;
    node->prev = p;
    p->next->prev = node;
    p->next = node;
}

template <class T>
void LinkedList<T>::insert_before(Node<T>* p, T element) {
    Node<T>* node = new Node<T>(element);

    node->next = p;
    node->prev = p->prev;
    p->prev->next = node;
    p->prev = node;
}

template <class T>
void LinkedList<T>::insert_first(T element) {
    insert_after(head, element);
}

template <class T>
void LinkedList<T>::insert_last(T element) {
    insert_before(tail, element);
}

template <class T>
Node<T>* LinkedList<T>::search(T element) {
    Node<T>* current = head->next;

    while (current != tail) {
        if (current->element() == element) {
            return current;
        }
        current = current->next;
    }

    return nullptr;
}

template <class T>
void LinkedList<T>::remove(Node<T>* p) {
    p->prev->next = p->next;
    p->next->prev = p->prev;

    delete p;
}

template <class T>
Iterator<T>* LinkedList<T>::create_iterator(bool forward) {
    Iterator<T>* iter;

    if (forward) {
        iter = new ForwardIterator<T>(this);
    } else {
        iter = new BackwardIterator<T>(this);
    }

    iter->first();

    return iter;
}

template <class T>
void LinkedList<T>::destroy_iterator(Iterator<T>* iter) {
    delete iter;
}

template <class T>
Iterator<T>::Iterator(LinkedList<T>* list) {
    this->list = list;
    current = nullptr;
}

template <class T>
bool Iterator<T>::is_done() const {
    return !current;
}

template <class T>
T Iterator<T>::current_item() const {
    return current->element();
}

template <class T>
void ForwardIterator<T>::first() {
    this->current = this->list->first();
}

template <class T>
void ForwardIterator<T>::next() {
    this->current = this->list->after(this->current);
}

template <class T>
void BackwardIterator<T>::first() {
    this->current = this->list->last();
}

template <class T>
void BackwardIterator<T>::next() {
    this->current = this->list->before(this->current);
}

}
}
}

#endif
