#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

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
    Node<T> *root;
public:
    BinaryTree(Node<T> *);
    ~BinaryTree();

    Node<T> *get_root();
    Node<T> *get_parent(Node<T> *);
    Node<T> *get_child(Node<T> *, bool);
    void set_child(Node<T> *, Node<T> *, bool);

    int depth(Node<T> *);
};

#include "binary_tree.tpp"

#endif
