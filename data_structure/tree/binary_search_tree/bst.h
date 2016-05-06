#ifndef BST_H_
#define BST_H_

#include "binary_tree.h"

template <class T>
class BST : public BinaryTree<T> {
public:
    BST() : BinaryTree<T>(NULL) {}

    void insert(T);

    Node<T> *search(Node<T> *, T);
    Node<T> *search(T);
};

#include "bst.tpp"

#endif
