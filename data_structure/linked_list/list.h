#ifndef LIST_H_
#define LIST_H_

#include <stddef.h>

template <class T>
class LinkedList;

template <class T>
class Node {
private:
    Node *next;
    Node *prev;
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
};

#include "list.tpp"

#endif /* LIST_H_ */
