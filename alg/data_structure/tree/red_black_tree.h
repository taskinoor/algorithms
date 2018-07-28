#ifndef ALG_DS_TREE_RED_BLACK_TREE_H_
#define ALG_DS_TREE_RED_BLACK_TREE_H_

#include "alg/data_structure/tree/binary_search_tree.h"
#include "alg/data_structure/tree/binary_tree.h"

namespace alg {
namespace ds {
namespace tree {

template <class T> class RedBlackTree;

enum class RBColor {
    RED,
    BLACK
};

template <class T>
class RBNode : public Node<T> {
public:
    explicit RBNode(RBColor color, const T& element = T(),
            Node<T>* parent = nullptr, Node<T>* left = nullptr,
            Node<T>* right = nullptr);

    RBColor color() const;

private:
    RBColor color_;

    friend class RedBlackTree<T>;
};

template <class T>
class RedBlackTree : public BinarySearchTree<T> {
public:
    RedBlackTree();

    void rotate(Node<T>* x, bool left);
    void insert(T element) override;
    void remove(Node<T>* z) override;

private:
    void insert_fixup(RBNode<T>* node);
    void remove_fixup(RBNode<T>* x);
};

template <class T>
RBNode<T>::RBNode(RBColor color, const T& element, Node<T>* parent,
        Node<T>* left, Node<T>* right) :
        Node<T>(element, parent, left, right),
        color_{color} {}

template <class T>
RBColor RBNode<T>::color() const {
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
void RedBlackTree<T>::rotate(Node<T>* x, bool left) {
    Node<T>* y = left ? this->right(x) : this->left(x);
    Node<T>* p = this->parent(x);

    if (y == this->nil_) {
        return;
    }

    if (left) {
        this->set_right(x, this->left(y));
    } else {
        this->set_left(x, this->right(y));
    }

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
        RBNode<T>* parent = static_cast<RBNode<T>*>(this->parent(node));

        if (parent->color_ == RBColor::BLACK) {
            break;
        }

        RBNode<T>* grandparent = static_cast<RBNode<T>*>(this->parent(parent));
        bool left = this->left(grandparent) == parent;

        RBNode<T>* uncle = static_cast<RBNode<T>*>(
                left ? this->right(grandparent) : this->left(grandparent));

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

                parent = static_cast<RBNode<T>*>(this->parent(node));
            }

            parent->color_ = RBColor::BLACK;
            grandparent->color_ = RBColor::RED;
            rotate(grandparent, !left);
        }
    }

    static_cast<RBNode<T>*>(this->root())->color_ = RBColor::BLACK;
}

template <class T>
void RedBlackTree<T>::remove(Node<T>* z) {
    RBNode<T>* x = nullptr;
    RBNode<T>* y = static_cast<RBNode<T>*>(z);
    RBColor y_color = y->color_;

    if (this->left(z) == this->nil_) {
        x = static_cast<RBNode<T>*>(this->right(z));

        this->transplant(z, x);
    } else if (this->right(z) == this->nil_) {
        x = static_cast<RBNode<T>*>(this->left(z));

        this->transplant(z, x);
    } else {
        y = static_cast<RBNode<T>*>(this->min(this->right(z)));
        x = static_cast<RBNode<T>*>(this->right(y));

        y_color = y->color_;

        if (this->parent(y) == z) {
            this->set_parent(y, x);
        } else {
            this->transplant(y, x);
            this->set_right(y, this->right(z));
        }

        this->transplant(z, y);
        this->set_left(y, this->left(z));

        y->color_ = static_cast<RBNode<T>*>(z)->color_;
    }

    if (y_color == RBColor::BLACK) {
        remove_fixup(x);
    }

    delete z;
}

template <class T>
void RedBlackTree<T>::remove_fixup(RBNode<T>* x) {
    while (x != this->root() && x->color_ == RBColor::BLACK) {
        RBNode<T>* p = static_cast<RBNode<T>*>(this->parent(x));
        bool left = this->left(p) == x;

        RBNode<T>* w = static_cast<RBNode<T>*>(
                left ? this->right(p) : this->left(p));

        if (w->color_ == RBColor::RED) {
            w->color_ = RBColor::BLACK;
            p->color_ = RBColor::RED;

            rotate(p, left);

            w = static_cast<RBNode<T>*>(left ? this->right(p) : this->left(p));
        }

        RBNode<T>* w_left = static_cast<RBNode<T>*>(this->left(w));
        RBNode<T>* w_right = static_cast<RBNode<T>*>(this->right(w));

        if (w_left->color_ == RBColor::BLACK &&
                w_right->color_ == RBColor::BLACK) {

            w->color_ = RBColor::RED;
            x = p;
        } else {
            bool rotation_needed = left ? w_right->color_ == RBColor::BLACK
                    : w_left->color_ == RBColor::BLACK;

            if (rotation_needed) {
                if (left) {
                    w_left->color_ = RBColor::BLACK;
                } else {
                    w_right->color_ = RBColor::BLACK;
                }

                w->color_ = RBColor::RED;

                rotate(w, !left);

                w = static_cast<RBNode<T>*>(
                        left ? this->right(p) : this->left(p));

                w_left = static_cast<RBNode<T>*>(this->left(w));
                w_right = static_cast<RBNode<T>*>(this->right(w));
            }

            w->color_ = p->color_;
            p->color_ = RBColor::BLACK;

            if (left) {
                w_right->color_ = RBColor::BLACK;
            } else {
                w_left->color_ = RBColor::BLACK;
            }

            rotate(p, left);

            x = static_cast<RBNode<T>*>(this->root());
        }
    }

    x->color_ = RBColor::BLACK;
}

}
}
}

#endif
