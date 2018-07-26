#ifndef ALG_DS_TREE_BINARY_TREE_H_
#define ALG_DS_TREE_BINARY_TREE_H_

#include <cstddef>

#include <algorithm>
#include <ostream>
#include <sstream>
#include <string>

namespace alg {
namespace ds {
namespace tree {

template <class T> class BinaryTree;

template <class T>
class Node {
public:
    explicit Node(const T& element = T(), Node<T>* parent = nullptr,
            Node<T>* left = nullptr, Node<T>* right = nullptr);

    virtual ~Node() = default;

    T& element();
    const T& element() const;

    virtual std::string to_string(Node<T>* nil = nullptr) const;

protected:
    Node<T>* parent;
    Node<T>* left;
    Node<T>* right;

    T element_;

    friend class BinaryTree<T>;
};

template <class T>
class BinaryTree {
public:
    explicit BinaryTree(Node<T>* root);
    virtual ~BinaryTree();

    Node<T>* root();
    const Node<T>* root() const;

    Node<T>* parent(const Node<T>* p);
    const Node<T>* parent(const Node<T>* p) const;

    Node<T>* left(const Node<T>* p);
    const Node<T>* left(const Node<T>* p) const;

    Node<T>* right(const Node<T>* p);
    const Node<T>* right(const Node<T>* p) const;

    void set_root(Node<T>* r);
    void set_left(Node<T>* p, Node<T>* child);
    void set_right(Node<T>* p, Node<T>* child);
    void set_parent(Node<T>* p, Node<T>* child);

    std::size_t depth(const Node<T>* p) const;
    std::size_t count_descendants(const Node<T>* p) const;

    std::size_t height() const;
    std::size_t height(const Node<T>* p) const;

    std::string to_string() const;

    Node<T>* nil();
    const Node<T>* nil() const;

    void set_nil(Node<T>* nil_);

protected:
    Node<T>* nil_{nullptr};

private:
    Node<T>* root_;

    void to_string(const Node<T>* p, std::string& out) const;
    void free(const Node<T>* node);
};

template <class T>
Node<T>::Node(const T& element, Node<T>* parent, Node<T>* left, Node<T>* right) :
        parent{parent},
        left{left},
        right{right},
        element_{element} {}

template <class T>
T& Node<T>::element() {
    return element_;
}

template <class T>
const T& Node<T>::element() const {
    return element_;
}

template <class T>
std::string Node<T>::to_string(Node<T>* nil) const {
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
BinaryTree<T>::BinaryTree(Node<T>* root) : root_{root} {}

template <class T>
BinaryTree<T>::~BinaryTree() {
    free(root_);

    delete nil_;
}

template <class T>
void BinaryTree<T>::free(const Node<T>* node) {
    if (node == nil_) {
        return;
    }

    free(node->left);
    free(node->right);

    delete node;
}

template <class T>
Node<T>* BinaryTree<T>::root() {
    return root_;
}

template <class T>
const Node<T>* BinaryTree<T>::root() const {
    return root_;
}

template <class T>
Node<T>* BinaryTree<T>::parent(const Node<T>* p) {
    return p->parent;
}

template <class T>
const Node<T>* BinaryTree<T>::parent(const Node<T>* p) const {
    return p->parent;
}

template <class T>
Node<T>* BinaryTree<T>::left(const Node<T>* p) {
    return p->left;
}

template <class T>
const Node<T>* BinaryTree<T>::left(const Node<T>* p) const {
    return p->left;
}

template <class T>
Node<T>* BinaryTree<T>::right(const Node<T>* p) {
    return p->right;
}

template <class T>
const Node<T>* BinaryTree<T>::right(const Node<T>* p) const {
    return p->right;
}

template <class T>
void BinaryTree<T>::set_root(Node<T>* r) {
    root_ = r;

    if (root_) {
        root_->parent = nil_;
    }
}

template <class T>
void BinaryTree<T>::set_left(Node<T>* p, Node<T>* child) {
    if (child) {
        child->parent = p;
    }

    p->left = child;
}

template <class T>
void BinaryTree<T>::set_right(Node<T>* p, Node<T>* child) {
    if (child) {
        child->parent = p;
    }

    p->right = child;
}

template <class T>
void BinaryTree<T>::set_parent(Node<T>* p, Node<T>* child) {
    if (child) {
        child->parent = p;
    }
}

template <class T>
std::size_t BinaryTree<T>::depth(const Node<T>* p) const {
    std::size_t d = 0;

    while (p->parent != nil_) {
        p = p->parent;
        ++d;
    }

    return d;
}

template <class T>
std::size_t BinaryTree<T>::height() const {
    return height(root_);
}

template <class T>
std::size_t BinaryTree<T>::height(const Node<T>* p) const {
    if (p->left == nil_ && p->right == nil_) {
        return 0;
    }

    std::size_t left_height = p->left != nil_ ? height(p->left) : 0;
    std::size_t right_height = p->right != nil_ ? height(p->right) : 0;

    return 1 + std::max(left_height, right_height);
}

template <class T>
std::size_t BinaryTree<T>::count_descendants(const Node<T>* p) const {
    if (p == nil_) {
        return 0;
    }

    return 1 + count_descendants(p->left) + count_descendants(p->right);
}

template <class T>
std::string BinaryTree<T>::to_string() const {
    std::string out = "";
    to_string(root_, out);

    return out;
}

template <class T>
void BinaryTree<T>::to_string(const Node<T>* p, std::string& out) const {
    if (p == nil_) {
        return;
    }

    out += p->to_string(nil_);

    to_string(p->left, out);
    to_string(p->right, out);
}

template <class T>
Node<T>* BinaryTree<T>::nil() {
    return nil_;
}

template <class T>
const Node<T>* BinaryTree<T>::nil() const {
    return nil_;
}

template <class T>
void BinaryTree<T>::set_nil(Node<T>* nil_) {
    this->nil_ = nil_;
}

}
}
}

#endif
