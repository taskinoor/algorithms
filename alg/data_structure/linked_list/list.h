#ifndef LIST_H_
#define LIST_H_

#include <stddef.h>

#include "iterator.h"

template <class T> class LinkedList;
template <class T> class ListIterator;

template <class T>
class Node {
private:
    Node<T> *next;
    Node<T> *prev;
    T element;

    friend class LinkedList<T>;
public:
    Node(T element = T());
    T get_element();
};

template <class T>
class LinkedList {
private:
    Node<T> *head;
    Node<T> *tail;
public:
    LinkedList();
    ~LinkedList();

    Node<T> *first();
    Node<T> *last();
    Node<T> *after(Node<T> *);
    Node<T> *before(Node<T> *);

    void insert_after(Node<T> *, T);
    void insert_before(Node<T> *, T);
    void insert_first(T);
    void insert_last(T);

    Node<T> *search(T);
    void remove(Node<T> *);

    ListIterator<T> *create_iterator(bool forward=true);
    void destroy_iterator(ListIterator<T> *);
};

template <class T>
class ListIterator : public Iterator<T> {
protected:
    LinkedList<T> *list;
    Node<T> *current;
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

#include "list.tpp"

#endif
