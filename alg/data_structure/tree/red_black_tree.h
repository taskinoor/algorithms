#ifndef ALG_RED_BLACK_TREE_H_
#define ALG_RED_BLACK_TREE_H_

#include "alg/data_structure/tree/bst.h"

namespace alg {

template <class T> class RedBlackTree;

enum class RBColor {
    RED,
    BLACK
};

template <class T>
class RBNode : public TreeNode<T> {
public:
    RBNode(RBColor color, T element = T(), TreeNode<T>* parent = nullptr,
            TreeNode<T>* left = nullptr, TreeNode<T>* right = nullptr);

    RBColor color();

private:
    RBColor color_;

    friend class RedBlackTree<T>;
};

template <class T>
class RedBlackTree : public BST<T> {
public:
    RedBlackTree();

    void rotate(TreeNode<T>* x, bool left);
    void insert(T element) override;
    void remove(TreeNode<T>* z) override;

private:
    void insert_fixup(RBNode<T>* node);
    void remove_fixup(RBNode<T>* x);
};

template <class T>
RBNode<T>::RBNode(RBColor color, T element, TreeNode<T>* parent,
        TreeNode<T>* left, TreeNode<T>* right) :
        TreeNode<T>(element, parent, left, right) {

    color_ = color;
}

template <class T>
RBColor RBNode<T>::color() {
    return color_;
}

template <class T>
RedBlackTree<T>::RedBlackTree() {
    this->set_nil(new RBNode<T>(RBColor::BLACK));

    this->set_left(this->nil_, this->nil_);
    this->set_right(this->nil_, this->nil_);
    this->set_parent(this->nil_, this->nil_);

    this->set_root(this->nil_);
}

template <class T>
void RedBlackTree<T>::rotate(TreeNode<T>* x, bool left) {
    TreeNode<T>* y = left ? this->right(x) : this->left(x);
    TreeNode<T>* p = this->parent(x);

    if (y == this->nil_) {
        return;
    }

    left ? this->set_right(x, this->left(y)) : this->set_left(x, this->right(y));

    if (p == this->nil_) {
        this->set_root(y);
    } else if (x == this->left(p)) {
        this->set_left(p, y);
    } else {
        this->set_right(p, y);
    }

    left ? this->set_left(y, x) : this->set_right(y, x);
}

template <class T>
void RedBlackTree<T>::insert(T element) {
    RBNode<T>* node = new RBNode<T>(RBColor::RED, element,
            this->nil_, this->nil_, this->nil_);

    this->insert_node(node);
    insert_fixup(node);
}

template <class T>
void RedBlackTree<T>::insert_fixup(RBNode<T>* node) {
    while (true) {
        RBNode<T>* parent = (RBNode<T>*)this->parent(node);

        if (parent->color_ == RBColor::BLACK) {
            break;
        }

        RBNode<T>* grandparent = (RBNode<T>*)this->parent(parent);
        bool left = this->left(grandparent) == parent;
        RBNode<T>* uncle = left ? (RBNode<T>*)this->right(grandparent) :
                (RBNode<T>*)this->left(grandparent);

        if (uncle->color_ == RBColor::RED) {
            parent->color_ = RBColor::BLACK;
            uncle->color_ = RBColor::BLACK;
            grandparent->color_ = RBColor::RED;

            node = grandparent;
        } else {
            bool rotation_needed =
                    (left ? this->right(parent) : this->left(parent)) == node;

            if (rotation_needed) {
                node = parent;
                rotate(node, left);
                parent = (RBNode<T>*)this->parent(node);
            }

            parent->color_ = RBColor::BLACK;
            grandparent->color_ = RBColor::RED;
            rotate(grandparent, !left);
        }
    }

    ((RBNode<T>*)this->root())->color_ = RBColor::BLACK;
}

template <class T>
void RedBlackTree<T>::remove(TreeNode<T>* z) {
    RBNode<T>* x = nullptr;
    RBNode<T>* y = (RBNode<T>*)z;
    RBColor y_color = y->color_;

    if (this->left(z) == this->nil_) {
        x = (RBNode<T>*)this->right(z);
        this->transplant(z, x);
    } else if (this->right(z) == this->nil_) {
        x = (RBNode<T>*)this->left(z);
        this->transplant(z, x);
    } else {
        y = (RBNode<T>*)this->min(this->right(z));
        x = (RBNode<T>*)this->right(y);
        y_color = y->color_;

        if (this->parent(y) == z) {
            this->set_parent(y, x);
        } else {
            this->transplant(y, x);
            this->set_right(y, this->right(z));
        }

        this->transplant(z, y);
        this->set_left(y, this->left(z));
        y->color_ = ((RBNode<T>*)z)->color_;
    }

    if (y_color == RBColor::BLACK) {
        remove_fixup(x);
    }

    delete z;
}

template <class T>
void RedBlackTree<T>::remove_fixup(RBNode<T>* x) {
    while (x != this->root() && x->color_ == RBColor::BLACK) {
        RBNode<T>* p = (RBNode<T>*)this->parent(x);
        bool left = this->left(p) == x;

        RBNode<T>* w = left ? (RBNode<T>*)this->right(p) :
                (RBNode<T>*)this->left(p);

        if (w->color_ == RBColor::RED) {
            w->color_ = RBColor::BLACK;
            p->color_ = RBColor::RED;
            rotate(p, left);
            w = left ? (RBNode<T>*)this->right(p) : (RBNode<T>*)this->left(p);
        }

        RBNode<T>* w_left = (RBNode<T>*)this->left(w);
        RBNode<T>* w_right = (RBNode<T>*)this->right(w);

        if (w_left->color_ == RBColor::BLACK &&
                w_right->color_ == RBColor::BLACK) {

            w->color_ = RBColor::RED;
            x = p;
        } else {
            bool rotation_needed = left ? w_right->color_ == RBColor::BLACK
                    : w_left->color_ == RBColor::BLACK;

            if (rotation_needed) {
                left ? w_left->color_ =
                        RBColor::BLACK : w_right->color_ = RBColor::BLACK;
                w->color_ = RBColor::RED;

                rotate(w, !left);

                w = left ? (RBNode<T>*)this->right(p) :
                        (RBNode<T>*)this->left(p);

                w_left = (RBNode<T>*)this->left(w);
                w_right = (RBNode<T>*)this->right(w);
            }

            w->color_ = p->color_;
            p->color_ = RBColor::BLACK;
            left ? w_right->color_ =
                    RBColor::BLACK : w_left->color_ = RBColor::BLACK;

            rotate(p, left);

            x = (RBNode<T>*)this->root();
        }
    }

    x->color_ = RBColor::BLACK;
}

}

#endif
