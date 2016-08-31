#ifndef ALG_BST_H_
#define ALG_BST_H_

#include "binary_tree.h"

namespace alg {

template <class T>
class BST : public BinaryTree<T> {
protected:
    void transplant(TreeNode<T> *, TreeNode<T> *);

public:
    BST() : BinaryTree<T>(NULL) {}

    virtual void insert(T);
    virtual void remove(TreeNode<T> *);

    TreeNode<T> *search(TreeNode<T> *, T);
    TreeNode<T> *search(T);

    TreeNode<T> *min(TreeNode<T> *);
    TreeNode<T> *min();

    TreeNode<T> *max(TreeNode<T> *);
    TreeNode<T> *max();

    TreeNode<T> *successor(TreeNode<T> *);
    TreeNode<T> *predecessor(TreeNode<T> *);
};

}

#include "bst.tpp"

#endif
