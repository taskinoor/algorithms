#ifndef ALG_LIST_H_
#define ALG_LIST_H_

#include <stddef.h>

#include "iterator.h"

namespace alg {

template <class T> class LinkedList;
template <class T> class ListIterator;

template <class T>
class ListNode {
private:
    ListNode<T> *next;
    ListNode<T> *prev;
    T element;

    friend class LinkedList<T>;
public:
    ListNode(T element = T());
    T get_element();
};

template <class T>
class LinkedList {
private:
    ListNode<T> *head;
    ListNode<T> *tail;
public:
    LinkedList();
    ~LinkedList();

    ListNode<T> *first();
    ListNode<T> *last();
    ListNode<T> *after(ListNode<T> *);
    ListNode<T> *before(ListNode<T> *);

    void insert_after(ListNode<T> *, T);
    void insert_before(ListNode<T> *, T);
    void insert_first(T);
    void insert_last(T);

    ListNode<T> *search(T);
    void remove(ListNode<T> *);

    ListIterator<T> *create_iterator(bool forward=true);
    void destroy_iterator(ListIterator<T> *);
};

template <class T>
class ListIterator : public Iterator<T> {
protected:
    LinkedList<T> *list;
    ListNode<T> *current;
public:
    ListIterator(LinkedList<T> *);

    virtual bool is_done() const;
    virtual T current_item() const;
};

template <class T>
class ForwardListIterator : public ListIterator<T> {
public:
    ForwardListIterator(LinkedList<T> *list) : ListIterator<T>(list) {}

    virtual void first();
    virtual void next();
};

template <class T>
class BackwordListIterator : public ListIterator<T> {
public:
    BackwordListIterator(LinkedList<T> *list) : ListIterator<T>(list) {}

    virtual void first();
    virtual void next();
};

}

#include "list.tpp"

#endif
