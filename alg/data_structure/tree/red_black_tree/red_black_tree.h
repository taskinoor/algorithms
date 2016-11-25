#ifndef ALG_RED_BLACK_TREE_H_
#define ALG_RED_BLACK_TREE_H_

#include "alg/data_structure/tree/binary_search_tree/bst.h"

namespace alg {

template <class T> class RedBlackTree;

enum RBColor {
    RED,
    BLACK
};

template <class T>
class RBNode : public TreeNode<T> {
private:
    RBColor color_;

    friend class RedBlackTree<T>;

public:
    RBNode(RBColor color, T element = T(), TreeNode<T> *parent = nullptr,
            TreeNode<T> *left = nullptr, TreeNode<T> *right = nullptr);

    RBColor color();
};

template <class T>
class RedBlackTree : public BST<T> {
private:
    void insert_fixup(RBNode<T> *node);
    void remove_fixup(RBNode<T> *x);

public:
    RedBlackTree();

    void rotate(TreeNode<T> *x, bool left);
    void insert(T element) override;
    void remove(TreeNode<T> *z) override;
};

}

#include "red_black_tree.tpp"

#endif
