#ifndef ALG_ORDER_STATISTIC_TREE_H_
#define ALG_ORDER_STATISTIC_TREE_H_

#include "alg/data_structure/tree/binary_tree.h"
#include "alg/data_structure/tree/bst.h"

namespace alg {

template <class T> class OrderStatisticTree;

template <class T>
class OSTNode : public TreeNode<T> {
public:
    explicit OSTNode(T element = T(), TreeNode<T>* parent = nullptr,
            TreeNode<T>* left = nullptr, TreeNode<T>* right = nullptr);

    int count();

private:
    int count_;

    friend class OrderStatisticTree<T>;
};

template <class T>
class OrderStatisticTree : public BST<T> {
public:
    void insert(T element) override;
    void remove(TreeNode<T>* z) override;

    T select(int i);
    T select(int i, OSTNode<T>* v);

    TreeNode<T>* select_node(int i);
    TreeNode<T>* select_node(int i, OSTNode<T>* v);

    int rank(T element);

private:
    void decrement_count(TreeNode<T>* node, TreeNode<T>* until);
};

template <class T>
OSTNode<T>::OSTNode(T element, TreeNode<T>* parent, TreeNode<T>* left,
        TreeNode<T>* right) : TreeNode<T>(element, parent, left, right) {

    count_ = 1;
}

template <class T>
int OSTNode<T>::count() {
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
        last->count_++;

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
void OrderStatisticTree<T>::remove(TreeNode<T>* z) {
    if (this->left(z) == this->nil_) {
        this->transplant(z, this->right(z));
    } else if (this->right(z) == this->nil_) {
        this->transplant(z, this->left(z));
    } else {
        TreeNode<T>* y = this->min(this->right(z));

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
void OrderStatisticTree<T>::decrement_count(
        TreeNode<T>* node, TreeNode<T>* until) {

    OSTNode<T>* parent = (OSTNode<T>*)this->parent(node);

    while (parent != until) {
        parent->count_--;
        parent = (OSTNode<T>*)this->parent(parent);
    }
}

template <class T>
T OrderStatisticTree<T>::select(int i) {
    return select(i, (OSTNode<T>*)this->root());
}

template <class T>
T OrderStatisticTree<T>::select(int i, OSTNode<T>* v) {
    return select_node(i, v)->element();
}

template <class T>
TreeNode<T>* OrderStatisticTree<T>::select_node(int i) {
    return select_node(i, (OSTNode<T>*)this->root());
}

template <class T>
TreeNode<T>* OrderStatisticTree<T>::select_node(int i, OSTNode<T>* v) {
    OSTNode<T>* left = (OSTNode<T>*)this->left(v);
    int count = left != this->nil_ ? left->count_ : 0;

    if (i == count) {
        return v;
    } else if (i < count) {
        return select_node(i, left);
    } else {
        return select_node(i - count - 1, (OSTNode<T>*)this->right(v));
    }
}

template <class T>
int OrderStatisticTree<T>::rank(T element) {
    TreeNode<T>* node = this->search(element);

    if (node == this->nil_) {
        return -1;
    }

    OSTNode<T>* left = (OSTNode<T>*)this->left(node);
    TreeNode<T>* root = this->root();

    int r = left != this->nil_ ? left->count() : 0;

    while (node != root) {
        TreeNode<T>* parent = this->parent(node);

        if (node == this->right(parent)) {
            left = (OSTNode<T>*)this->left(parent);
            r += (left != this->nil_ ? left->count() : 0) + 1;
        }

        node = parent;
    }

    return r;
}

}

#endif
