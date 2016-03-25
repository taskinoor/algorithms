#ifndef LIST_H_
#define LIST_H_

#include <stddef.h>

template <class T>
class Node {
private:
    Node *next;
    Node *prev;
    T element;
public:
    Node(T element = T());
    T get_element();
};

#include "list.tpp"

#endif /* LIST_H_ */
