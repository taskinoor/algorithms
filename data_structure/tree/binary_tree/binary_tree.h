#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

template <class T>
class Node {
private:
    Node<T> *parent;
    Node<T> *left;
    Node<T> *right;

    T element;
public:
    Node(T element = T());
    ~Node();

    T get_element();
};

#include "binary_tree.tpp"

#endif
