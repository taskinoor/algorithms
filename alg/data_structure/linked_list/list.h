#ifndef ALG_LIST_H_
#define ALG_LIST_H_

#include "alg/common/iterator.h"

namespace alg {

template <class T> class LinkedList;
template <class T> class ListIterator;

template <class T>
class ListNode {
private:
    ListNode<T> *next;
    ListNode<T> *prev;
    T element_;

    friend class LinkedList<T>;
public:
    ListNode(T element = T());

    T element();
};

template <class T>
class LinkedList {
private:
    ListNode<T> *head;
    ListNode<T> *tail;

public:
    LinkedList();
    virtual ~LinkedList();

    ListNode<T> *first();
    ListNode<T> *last();
    ListNode<T> *after(ListNode<T> *p);
    ListNode<T> *before(ListNode<T> *p);

    void insert_after(ListNode<T> *p, T element);
    void insert_before(ListNode<T> *p, T element);
    void insert_first(T element);
    void insert_last(T element);

    ListNode<T> *search(T element);
    void remove(ListNode<T> *p);

    ListIterator<T> *create_iterator(bool forward = true);
    void destroy_iterator(ListIterator<T> *iter);
};

template <class T>
class ListIterator : public Iterator<T> {
protected:
    LinkedList<T> *list;
    ListNode<T> *current;

public:
    ListIterator(LinkedList<T> *list);
    virtual ~ListIterator() {}

    virtual bool is_done() const;
    virtual T current_item() const;
};

template <class T>
class ForwardListIterator : public ListIterator<T> {
public:
    ForwardListIterator(LinkedList<T> *list) : ListIterator<T>(list) {}

    void first();
    void next();
};

template <class T>
class BackwardListIterator : public ListIterator<T> {
public:
    BackwardListIterator(LinkedList<T> *list) : ListIterator<T>(list) {}

    void first();
    void next();
};

template <class T>
ListNode<T>::ListNode(T element) {
    prev = nullptr;
    next = nullptr;
    element_ = element;
}

template <class T>
T ListNode<T>::element() {
    return element_;
}

template <class T>
LinkedList<T>::LinkedList() {
    head = new ListNode<T>;
    tail = new ListNode<T>;

    head->next = tail;
    tail->prev = head;
}

template <class T>
LinkedList<T>::~LinkedList() {
    ListNode<T> *current = head->next;

    while (current != tail) {
        ListNode<T> *next = current->next;
        delete current;
        current = next;
    }

    delete head;
    delete tail;
}

template <class T>
ListNode<T> *LinkedList<T>::first() {
    return after(head);
}

template <class T>
ListNode<T> *LinkedList<T>::last() {
    return before(tail);
}

template <class T>
ListNode<T> *LinkedList<T>::after(ListNode<T> *p) {
    if (p->next == tail) {
        return nullptr;
    }

    return p->next;
}

template <class T>
ListNode<T> *LinkedList<T>::before(ListNode<T> *p) {
    if (p->prev == head) {
        return nullptr;
    }

    return p->prev;
}

template <class T>
void LinkedList<T>::insert_after(ListNode<T> *p, T element) {
    ListNode<T> *node = new ListNode<T>(element);

    node->next = p->next;
    node->prev = p;
    p->next->prev = node;
    p->next = node;
}

template <class T>
void LinkedList<T>::insert_before(ListNode<T> *p, T element) {
    ListNode<T> *node = new ListNode<T>(element);

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
ListNode<T> *LinkedList<T>::search(T element) {
    ListNode<T> *current = head->next;

    while (current != tail) {
        if (current->element() == element) {
            return current;
        }
        current = current->next;
    }

    return nullptr;
}

template <class T>
void LinkedList<T>::remove(ListNode<T> *p) {
    p->prev->next = p->next;
    p->next->prev = p->prev;

    delete p;
}

template <class T>
ListIterator<T> *LinkedList<T>::create_iterator(bool forward) {
    ListIterator<T> *iter;

    if (forward) {
        iter = new ForwardListIterator<T>(this);
    } else {
        iter = new BackwardListIterator<T>(this);
    }

    iter->first();

    return iter;
}

template <class T>
void LinkedList<T>::destroy_iterator(ListIterator<T> *iter) {
    delete iter;
}

template <class T>
ListIterator<T>::ListIterator(LinkedList<T> *list) {
    this->list = list;
    current = nullptr;
}

template <class T>
bool ListIterator<T>::is_done() const {
    return !current;
}

template <class T>
T ListIterator<T>::current_item() const {
    return current->element();
}

template <class T>
void ForwardListIterator<T>::first() {
    this->current = this->list->first();
}

template <class T>
void ForwardListIterator<T>::next() {
    this->current = this->list->after(this->current);
}

template <class T>
void BackwardListIterator<T>::first() {
    this->current = this->list->last();
}

template <class T>
void BackwardListIterator<T>::next() {
    this->current = this->list->before(this->current);
}

}

#endif
