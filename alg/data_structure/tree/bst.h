#ifndef ALG_BST_H_
#define ALG_BST_H_

#include "alg/data_structure/tree/binary_tree.h"

namespace alg {

template <class T>
class BST : public BinaryTree<T> {
protected:
    void transplant(TreeNode<T> *u, TreeNode<T> *v);

public:
    BST() : BinaryTree<T>(nullptr) {}
    virtual ~BST() = default;

    virtual void insert(T element);
    virtual void insert_node(TreeNode<T> *node);

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

template <class T>
void BST<T>::insert(T element) {
    TreeNode<T> *node = new TreeNode<T>(element,
            this->nil_, this->nil_, this->nil_);

    insert_node(node);
}

template <class T>
void BST<T>::insert_node(TreeNode<T> *node) {
    TreeNode<T> *last = nullptr;
    TreeNode<T> *current = this->root();

    while (current != this->nil_) {
        last = current;

        if (node->element() < current->element()) {
            current = this->left(current);
        } else {
            current = this->right(current);
        }
    }

    if (!last) {
        this->set_root(node);
    } else if (node->element() < last->element()) {
        this->set_left(last, node);
    } else {
        this->set_right(last, node);
    }
}

template <class T>
TreeNode<T> *BST<T>::search(TreeNode<T> *node, T key) {
    while (node != this->nil_ && node->element() != key) {
        if (key < node->element()) {
             node = this->left(node);
        } else {
            node = this->right(node);
        }
    }

    return node;
}

template <class T>
TreeNode<T> *BST<T>::search(T key) {
    return search(this->root(), key);
}

template <class T>
TreeNode<T> *BST<T>::min(TreeNode<T> *node) {
    while (node != this->nil_ && this->left(node) != this->nil_) {
        node = this->left(node);
    }

    return node;
}

template <class T>
TreeNode<T> *BST<T>::min() {
    return min(this->root());
}

template <class T>
TreeNode<T> *BST<T>::max(TreeNode<T> *node) {
    while (node != this->nil_ && this->right(node) != this->nil_) {
        node = this->right(node);
    }

    return node;
}

template <class T>
TreeNode<T> *BST<T>::max() {
    return max(this->root());
}

template <class T>
TreeNode<T> *BST<T>::successor(TreeNode<T> *node) {
    if (this->right(node) != this->nil_) {
        return min(this->right(node));
    }

    TreeNode<T> *p = this->parent(node);

    while (p != this->nil_ && this->right(p) == node) {
        node = p;
        p = this->parent(p);
    }

    return p;
}

template <class T>
TreeNode<T> *BST<T>::predecessor(TreeNode<T> *node) {
    if (this->left(node) != this->nil_) {
        return max(this->left(node));
    }

    TreeNode<T> *p = this->parent(node);

    while (p != this->nil_ && this->left(p) == node) {
        node = p;
        p = this->parent(p);
    }

    return p;
}

template <class T>
void BST<T>::transplant(TreeNode<T> *u, TreeNode<T> *v) {
    TreeNode<T> *p = this->parent(u);

    if (p == this->nil_) {
        this->set_root(v);
    } else {
        if (this->left(p) == u) {
            this->set_left(p, v);
        } else {
            this->set_right(p, v);
        }
    }
}

template <class T>
void BST<T>::remove(TreeNode<T> *z) {
    if (this->left(z) == this->nil_) {
        transplant(z, this->right(z));
    } else if (this->right(z) == this->nil_) {
        transplant(z, this->left(z));
    } else {
        TreeNode<T> *y = min(this->right(z));

        if (this->parent(y) != z) {
            transplant(y, this->right(y));
            this->set_right(y, this->right(z));
        }

        transplant(z, y);
        this->set_left(y, this->left(z));
    }

    delete z;
}

}

#endif
