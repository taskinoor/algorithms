#ifndef ALG_BINARY_TREE_H_
#define ALG_BINARY_TREE_H_

#include <sstream>
#include <string>

#include "alg/common/utils.h"

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
    TreeNode(T element = T(), TreeNode<T> *parent = nullptr,
            TreeNode<T> *left = nullptr, TreeNode<T> *right = nullptr);

    virtual ~TreeNode() {}

    T element();
    virtual std::string to_string(TreeNode<T> *nil = nullptr);
};

template <class T>
class BinaryTree {
private:
    TreeNode<T> *root_;

    void to_string(TreeNode<T> *p, std::string& out);
    void free(TreeNode<T> *node);

protected:
    TreeNode<T> *nil_;

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
    void set_parent(TreeNode<T> *p, TreeNode<T> *child);

    int depth(TreeNode<T> *p);
    int height();
    int height(TreeNode<T> *p);
    int count_descendants(TreeNode<T> *p);

    std::string to_string();

    TreeNode<T> *nil();
    void set_nil(TreeNode<T> *nil_);
};

}

#include "binary_tree.tpp"

#endif
