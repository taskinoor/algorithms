#ifndef ALG_LIST_H_
#define ALG_LIST_H_

#include "iterator.h"

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

}

#include "list.tpp"

#endif
