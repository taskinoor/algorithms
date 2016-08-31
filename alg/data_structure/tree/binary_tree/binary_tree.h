#ifndef ALG_BINARY_TREE_H_
#define ALG_BINARY_TREE_H_

#include <iostream>
#include <string>

#include "utils.h"

namespace alg {

template <class T> class BinaryTree;

template <class T>
class TreeNode {
    friend class BinaryTree<T>;

protected:
    TreeNode<T> *parent;
    TreeNode<T> *left;
    TreeNode<T> *right;

    T element;

public:
    TreeNode(T element = T());
    virtual ~TreeNode();

    T get_element();
};

template <class T>
class BinaryTree {
private:
    TreeNode<T> *_root;

public:
    BinaryTree(TreeNode<T> *);
    virtual ~BinaryTree();

    TreeNode<T> *root();
    TreeNode<T> *parent(TreeNode<T> *);
    TreeNode<T> *left(TreeNode<T> *);
    TreeNode<T> *right(TreeNode<T> *);

    void set_root(TreeNode<T> *);
    void set_left(TreeNode<T> *, TreeNode<T> *);
    void set_right(TreeNode<T> *, TreeNode<T> *);

    int depth(TreeNode<T> *);
    int height();
    int height(TreeNode<T> *);
    int count_descendants(TreeNode<T> *);

    void print();
    void print(TreeNode<T> *);
};

}

#include "binary_tree.tpp"

#endif
