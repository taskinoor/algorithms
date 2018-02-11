#ifndef ALG_DS_TREE_BINARY_SEARCH_TREE_H_
#define ALG_DS_TREE_BINARY_SEARCH_TREE_H_

#include "alg/data_structure/tree/binary_tree.h"

namespace alg {
namespace ds {
namespace tree {

template <class T>
class BinarySearchTree : public BinaryTree<T> {
public:
    BinarySearchTree() : BinaryTree<T>(nullptr) {}
    virtual ~BinarySearchTree() = default;

    virtual void insert(T element);
    virtual void insert_node(Node<T>* node);

    virtual void remove(Node<T>* z);

    Node<T>* search(Node<T>* node, T key);
    Node<T>* search(T key);

    Node<T>* min(Node<T>* node);
    Node<T>* min();

    Node<T>* max(Node<T>* node);
    Node<T>* max();

    Node<T>* successor(Node<T>* node);
    Node<T>* predecessor(Node<T>* node);

protected:
    void transplant(Node<T>* u, Node<T>* v);
};

template <class T>
void BinarySearchTree<T>::insert(T element) {
    Node<T>* node = new Node<T>(element, this->nil_, this->nil_, this->nil_);

    insert_node(node);
}

template <class T>
void BinarySearchTree<T>::insert_node(Node<T>* node) {
    Node<T>* last = nullptr;
    Node<T>* current = this->root();

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
Node<T>* BinarySearchTree<T>::search(Node<T>* node, T key) {
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
Node<T>* BinarySearchTree<T>::search(T key) {
    return search(this->root(), key);
}

template <class T>
Node<T>* BinarySearchTree<T>::min(Node<T>* node) {
    while (node != this->nil_ && this->left(node) != this->nil_) {
        node = this->left(node);
    }

    return node;
}

template <class T>
Node<T>* BinarySearchTree<T>::min() {
    return min(this->root());
}

template <class T>
Node<T>* BinarySearchTree<T>::max(Node<T>* node) {
    while (node != this->nil_ && this->right(node) != this->nil_) {
        node = this->right(node);
    }

    return node;
}

template <class T>
Node<T>* BinarySearchTree<T>::max() {
    return max(this->root());
}

template <class T>
Node<T>* BinarySearchTree<T>::successor(Node<T>* node) {
    if (this->right(node) != this->nil_) {
        return min(this->right(node));
    }

    Node<T>* p = this->parent(node);

    while (p != this->nil_ && this->right(p) == node) {
        node = p;
        p = this->parent(p);
    }

    return p;
}

template <class T>
Node<T>* BinarySearchTree<T>::predecessor(Node<T>* node) {
    if (this->left(node) != this->nil_) {
        return max(this->left(node));
    }

    Node<T>* p = this->parent(node);

    while (p != this->nil_ && this->left(p) == node) {
        node = p;
        p = this->parent(p);
    }

    return p;
}

template <class T>
void BinarySearchTree<T>::transplant(Node<T>* u, Node<T>* v) {
    Node<T>* p = this->parent(u);

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
void BinarySearchTree<T>::remove(Node<T>* z) {
    if (this->left(z) == this->nil_) {
        transplant(z, this->right(z));
    } else if (this->right(z) == this->nil_) {
        transplant(z, this->left(z));
    } else {
        Node<T>* y = min(this->right(z));

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
}
}

#endif
