#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include "utils.h"

template <class T> class BinaryTree;

template <class T>
class Node {
private:
    Node<T> *parent;
    Node<T> *left;
    Node<T> *right;

    T element;

    friend class BinaryTree<T>;
public:
    Node(T element = T());
    ~Node();

    T get_element();
};

template <class T>
class BinaryTree {
private:
    Node<T> *_root;
public:
    BinaryTree(Node<T> *);
    ~BinaryTree();

    Node<T> *root();
    Node<T> *parent(Node<T> *);
    Node<T> *left(Node<T> *);
    Node<T> *right(Node<T> *);

    void set_left(Node<T> *, Node<T> *);
    void set_right(Node<T> *, Node<T> *);

    int depth(Node<T> *);
    int height();
    int height(Node<T> *);
    int count_descendants(Node<T> *);
};

#include "binary_tree.tpp"

#endif
