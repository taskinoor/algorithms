#ifndef ALG_DS_TREE_ORDER_STATISTIC_TREE_H_
#define ALG_DS_TREE_ORDER_STATISTIC_TREE_H_

#include <cstddef>

#include "alg/common/exception.h"
#include "alg/data_structure/tree/binary_search_tree.h"
#include "alg/data_structure/tree/binary_tree.h"

namespace alg {
namespace ds {
namespace tree {

template <class T> class OrderStatisticTree;

template <class T>
class OSTNode : public Node<T> {
public:
    explicit OSTNode(const T& element = T(), Node<T>* parent = nullptr,
            Node<T>* left = nullptr, Node<T>* right = nullptr);

    std::size_t count() const;

private:
    std::size_t count_{1};

    friend class OrderStatisticTree<T>;
};

template <class T>
class OrderStatisticTree : public BinarySearchTree<T> {
public:
    void insert(T element) override;
    void remove(Node<T>* z) override;

    T select(std::size_t i);
    T select(std::size_t i, OSTNode<T>* v);

    Node<T>* select_node(std::size_t i);
    Node<T>* select_node(std::size_t i, OSTNode<T>* v);

    std::size_t rank(T element);

private:
    void decrement_count(Node<T>* node, Node<T>* until);
};

template <class T>
OSTNode<T>::OSTNode(const T& element, Node<T>* parent, Node<T>* left,
        Node<T>* right) : Node<T>(element, parent, left, right) {}

template <class T>
std::size_t OSTNode<T>::count() const {
    return count_;
}

template <class T>
void OrderStatisticTree<T>::insert(T element) {
    OSTNode<T>* last = nullptr;
    OSTNode<T>* current = (OSTNode<T>*)this->root();
    OSTNode<T>* node = new OSTNode<T>(element, this->nil_, this->nil_,
            this->nil_);

    while (current != this->nil_) {
        last = current;
        ++(last->count_);

        if (element < current->element()) {
            current = (OSTNode<T>*)this->left(current);
        } else {
            current = (OSTNode<T>*)this->right(current);
        }
    }

    if (!last) {
        this->set_root(node);
    } else if (element < last->element()) {
        this->set_left(last, node);
    } else {
        this->set_right(last, node);
    }
}

template <class T>
void OrderStatisticTree<T>::remove(Node<T>* z) {
    if (this->left(z) == this->nil_) {
        this->transplant(z, this->right(z));
    } else if (this->right(z) == this->nil_) {
        this->transplant(z, this->left(z));
    } else {
        Node<T>* y = this->min(this->right(z));

        if (this->parent(y) != z) {
            this->transplant(y, this->right(y));
            decrement_count(y, z);
            this->set_right(y, this->right(z));
        }

        this->transplant(z, y);
        ((OSTNode<T>*)y)->count_ = ((OSTNode<T>*)z)->count_ - 1;
        this->set_left(y, this->left(z));
    }

    decrement_count(z, this->nil_);

    delete z;
}

template <class T>
void OrderStatisticTree<T>::decrement_count(Node<T>* node, Node<T>* until) {

    OSTNode<T>* parent = (OSTNode<T>*)this->parent(node);

    while (parent != until) {
        --(parent->count_);
        parent = (OSTNode<T>*)this->parent(parent);
    }
}

template <class T>
T OrderStatisticTree<T>::select(std::size_t i) {
    return select(i, (OSTNode<T>*)this->root());
}

template <class T>
T OrderStatisticTree<T>::select(std::size_t i, OSTNode<T>* v) {
    return select_node(i, v)->element();
}

template <class T>
Node<T>* OrderStatisticTree<T>::select_node(std::size_t i) {
    return select_node(i, (OSTNode<T>*)this->root());
}

template <class T>
Node<T>* OrderStatisticTree<T>::select_node(std::size_t i, OSTNode<T>* v) {
    OSTNode<T>* left = (OSTNode<T>*)this->left(v);
    std::size_t count = left != this->nil_ ? left->count_ : 0;

    if (i == count) {
        return v;
    } else if (i < count) {
        return select_node(i, left);
    } else {
        return select_node(i - count - 1, (OSTNode<T>*)this->right(v));
    }
}

template <class T>
std::size_t OrderStatisticTree<T>::rank(T element) {
    Node<T>* node = this->search(element);

    if (node == this->nil_) {
        throw except::ItemNotFound();
    }

    OSTNode<T>* left = (OSTNode<T>*)this->left(node);
    Node<T>* root = this->root();

    std::size_t r = left != this->nil_ ? left->count() : 0;

    while (node != root) {
        Node<T>* parent = this->parent(node);

        if (node == this->right(parent)) {
            left = (OSTNode<T>*)this->left(parent);
            r += (left != this->nil_ ? left->count() : 0) + 1;
        }

        node = parent;
    }

    return r;
}

}
}
}

#endif
