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

    T element_;

public:
    TreeNode(T element = T());
    virtual ~TreeNode();

    T element();
};

template <class T>
class BinaryTree {
private:
    TreeNode<T> *root_;

public:
    BinaryTree(TreeNode<T> *root);
    virtual ~BinaryTree();

    TreeNode<T> *root();
    TreeNode<T> *parent(TreeNode<T> *p);
    TreeNode<T> *left(TreeNode<T> *p);
    TreeNode<T> *right(TreeNode<T> *p);

    void set_root(TreeNode<T> *r);
    void set_left(TreeNode<T> *p, TreeNode<T> *child);
    void set_right(TreeNode<T> *p, TreeNode<T> *child);

    int depth(TreeNode<T> *p);
    int height();
    int height(TreeNode<T> *p);
    int count_descendants(TreeNode<T> *p);

    void print();
    void print(TreeNode<T> *p);
};

}

#include "binary_tree.tpp"

#endif
