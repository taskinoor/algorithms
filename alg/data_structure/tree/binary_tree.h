#ifndef ALG_BINARY_TREE_H_
#define ALG_BINARY_TREE_H_

#include <sstream>
#include <string>

#include "alg/common/utils.h"

namespace alg {

template <class T> class BinaryTree;

template <class T>
class TreeNode {
public:
    TreeNode(T element = T(), TreeNode<T>* parent = nullptr,
            TreeNode<T>* left = nullptr, TreeNode<T>* right = nullptr);

    virtual ~TreeNode() {}

    T element();
    virtual std::string to_string(TreeNode<T>* nil = nullptr);

protected:
    TreeNode<T>* parent;
    TreeNode<T>* left;
    TreeNode<T>* right;

    T element_;

    friend class BinaryTree<T>;
};

template <class T>
class BinaryTree {
public:
    BinaryTree(TreeNode<T>* root);
    virtual ~BinaryTree();

    TreeNode<T>* root();
    TreeNode<T>* parent(TreeNode<T>* p);
    TreeNode<T>* left(TreeNode<T>* p);
    TreeNode<T>* right(TreeNode<T>* p);

    void set_root(TreeNode<T>* r);
    void set_left(TreeNode<T>* p, TreeNode<T>* child);
    void set_right(TreeNode<T>* p, TreeNode<T>* child);
    void set_parent(TreeNode<T>* p, TreeNode<T>* child);

    int depth(TreeNode<T>* p);
    int height();
    int height(TreeNode<T>* p);
    int count_descendants(TreeNode<T>* p);

    std::string to_string();

    TreeNode<T>* nil();
    void set_nil(TreeNode<T>* nil_);

protected:
    TreeNode<T>* nil_;

private:
    TreeNode<T>* root_;

    void to_string(TreeNode<T>* p, std::string& out);
    void free(TreeNode<T>* node);
};

template <class T>
TreeNode<T>::TreeNode(T element, TreeNode<T>* parent, TreeNode<T>* left,
        TreeNode<T>* right) {

    element_ = element;

    this->parent = parent;
    this->left = left;
    this->right = right;
}

template <class T>
T TreeNode<T>::element() {
    return element_;
}

template <class T>
std::string TreeNode<T>::to_string(TreeNode<T>* nil) {
    std::ostringstream buf;

    buf << "E: " << element_;

    if (left != nil) {
        buf << ", L: " << left->element();
    } else {
        buf << ", L: nil";
    }

    if (right != nil) {
        buf << ", R: " << right->element();
    } else {
        buf << ", R: nil";
    }

    if (parent != nil) {
        buf << ", P: " << parent->element();
    } else {
        buf << ", P: nil";
    }

    buf << std::endl;

    return buf.str();
}

template <class T>
BinaryTree<T>::BinaryTree(TreeNode<T>* root) {
   root_ = root;
   nil_ = nullptr;
}

template <class T>
BinaryTree<T>::~BinaryTree() {
    free(root_);
    delete nil_;
}

template <class T>
void BinaryTree<T>::free(TreeNode<T>* node) {
    if (node == nil_) {
        return;
    }

    free(node->left);
    free(node->right);

    delete node;
}

template <class T>
TreeNode<T>* BinaryTree<T>::root() {
    return root_;
}

template <class T>
TreeNode<T>* BinaryTree<T>::parent(TreeNode<T>* p) {
    return p->parent;
}

template <class T>
TreeNode<T>* BinaryTree<T>::left(TreeNode<T>* p) {
    return p->left;
}

template <class T>
TreeNode<T>* BinaryTree<T>::right(TreeNode<T>* p) {
    return p->right;
}

template <class T>
void BinaryTree<T>::set_root(TreeNode<T>* r) {
    root_ = r;

    if (root_) {
        root_->parent = nil_;
    }
}

template <class T>
void BinaryTree<T>::set_left(TreeNode<T>* p, TreeNode<T>* child) {
    if (child) {
        child->parent = p;
    }

    p->left = child;
}

template <class T>
void BinaryTree<T>::set_right(TreeNode<T>* p, TreeNode<T>* child) {
    if (child) {
        child->parent = p;
    }

    p->right = child;
}

template <class T>
void BinaryTree<T>::set_parent(TreeNode<T>* p, TreeNode<T>* child) {
    if (child) {
        child->parent = p;
    }
}

template <class T>
int BinaryTree<T>::depth(TreeNode<T>* p) {
    int d = 0;

    while (p->parent != nil_) {
        p = p->parent;
        d++;
    }

    return d;
}

template <class T>
int BinaryTree<T>::height() {
    return height(root_);
}

template <class T>
int BinaryTree<T>::height(TreeNode<T>* p) {
    if (p == nil_) {
        return -1;
    }

    return 1 + utils::max(height(p->left), height(p->right));
}

template <class T>
int BinaryTree<T>::count_descendants(TreeNode<T>* p) {
    if (p == nil_) {
        return 0;
    }

    return 1 + count_descendants(p->left) + count_descendants(p->right);
}

template <class T>
std::string BinaryTree<T>::to_string() {
    std::string out = "";
    to_string(root_, out);

    return out;
}

template <class T>
void BinaryTree<T>::to_string(TreeNode<T>* p, std::string& out) {
    if (p == nil_) {
        return;
    }

    out += p->to_string(nil_);

    to_string(p->left, out);
    to_string(p->right, out);
}

template <class T>
TreeNode<T>* BinaryTree<T>::nil() {
    return nil_;
}

template <class T>
void BinaryTree<T>::set_nil(TreeNode<T>* nil_) {
    this->nil_ = nil_;
}

}

#endif
