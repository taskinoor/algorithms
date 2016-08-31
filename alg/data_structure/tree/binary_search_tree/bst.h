#ifndef BST_H_
#define BST_H_

#include "binary_tree.h"

template <class T>
class BST : public BinaryTree<T> {
protected:
    void transplant(Node<T> *, Node<T> *);

public:
    BST() : BinaryTree<T>(NULL) {}

    virtual void insert(T);
    virtual void remove(Node<T> *);

    Node<T> *search(Node<T> *, T);
    Node<T> *search(T);

    Node<T> *min(Node<T> *);
    Node<T> *min();

    Node<T> *max(Node<T> *);
    Node<T> *max();

    Node<T> *successor(Node<T> *);
    Node<T> *predecessor(Node<T> *);
};

#include "bst.tpp"

#endif
