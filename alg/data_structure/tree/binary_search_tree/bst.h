#ifndef ALG_BST_H_
#define ALG_BST_H_

#include "binary_tree.h"

namespace alg {

template <class T>
class BST : public BinaryTree<T> {
protected:
    void transplant(TreeNode<T> *u, TreeNode<T> *v);

public:
    BST() : BinaryTree<T>(nullptr) {}

    virtual void insert(T element);
    virtual void remove(TreeNode<T> *z);

    TreeNode<T> *search(TreeNode<T> *node, T key);
    TreeNode<T> *search(T key);

    TreeNode<T> *min(TreeNode<T> *node);
    TreeNode<T> *min();

    TreeNode<T> *max(TreeNode<T> *node);
    TreeNode<T> *max();

    TreeNode<T> *successor(TreeNode<T> *node);
    TreeNode<T> *predecessor(TreeNode<T> *node);
};

}

#include "bst.tpp"

#endif
