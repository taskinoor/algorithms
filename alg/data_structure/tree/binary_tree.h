#ifndef ALG_BINARY_TREE_H_
#define ALG_BINARY_TREE_H_

#include <algorithm>
#include <ostream>
#include <sstream>
#include <string>

namespace alg {

template <class T> class BinaryTree;

template <class T>
class TreeNode {
public:
    explicit TreeNode(const T& element = T(), TreeNode<T>* parent = nullptr,
            TreeNode<T>* left = nullptr, TreeNode<T>* right = nullptr);

    virtual ~TreeNode() {}

    T& element();
    const T& element() const;

    virtual std::string to_string(TreeNode<T>* nil = nullptr) const;

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
    explicit BinaryTree(TreeNode<T>* root);
    virtual ~BinaryTree();

    TreeNode<T>* root();
    const TreeNode<T>* root() const;

    TreeNode<T>* parent(const TreeNode<T>* p);
    const TreeNode<T>* parent(const TreeNode<T>* p) const;

    TreeNode<T>* left(const TreeNode<T>* p);
    const TreeNode<T>* left(const TreeNode<T>* p) const;

    TreeNode<T>* right(const TreeNode<T>* p);
    const TreeNode<T>* right(const TreeNode<T>* p) const;

    void set_root(TreeNode<T>* r);
    void set_left(TreeNode<T>* p, TreeNode<T>* child);
    void set_right(TreeNode<T>* p, TreeNode<T>* child);
    void set_parent(TreeNode<T>* p, TreeNode<T>* child);

    int depth(const TreeNode<T>* p) const;
    int count_descendants(const TreeNode<T>* p) const;

    int height() const;
    int height(const TreeNode<T>* p) const;

    std::string to_string() const;

    TreeNode<T>* nil();
    const TreeNode<T>* nil() const;

    void set_nil(TreeNode<T>* nil_);

protected:
    TreeNode<T>* nil_;

private:
    TreeNode<T>* root_;

    void to_string(const TreeNode<T>* p, std::string& out) const;
    void free(const TreeNode<T>* node);
};

template <class T>
TreeNode<T>::TreeNode(const T& element, TreeNode<T>* parent, TreeNode<T>* left,
        TreeNode<T>* right) {

    element_ = element;

    this->parent = parent;
    this->left = left;
    this->right = right;
}

template <class T>
T& TreeNode<T>::element() {
    return element_;
}

template <class T>
const T& TreeNode<T>::element() const {
    return element_;
}

template <class T>
std::string TreeNode<T>::to_string(TreeNode<T>* nil) const {
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
void BinaryTree<T>::free(const TreeNode<T>* node) {
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
const TreeNode<T>* BinaryTree<T>::root() const {
    return root_;
}

template <class T>
TreeNode<T>* BinaryTree<T>::parent(const TreeNode<T>* p) {
    return p->parent;
}

template <class T>
const TreeNode<T>* BinaryTree<T>::parent(const TreeNode<T>* p) const {
    return p->parent;
}

template <class T>
TreeNode<T>* BinaryTree<T>::left(const TreeNode<T>* p) {
    return p->left;
}

template <class T>
const TreeNode<T>* BinaryTree<T>::left(const TreeNode<T>* p) const {
    return p->left;
}

template <class T>
TreeNode<T>* BinaryTree<T>::right(const TreeNode<T>* p) {
    return p->right;
}

template <class T>
const TreeNode<T>* BinaryTree<T>::right(const TreeNode<T>* p) const {
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
int BinaryTree<T>::depth(const TreeNode<T>* p) const {
    int d = 0;

    while (p->parent != nil_) {
        p = p->parent;
        ++d;
    }

    return d;
}

template <class T>
int BinaryTree<T>::height() const {
    return height(root_);
}

template <class T>
int BinaryTree<T>::height(const TreeNode<T>* p) const {
    if (p == nil_) {
        return -1;
    }

    return 1 + std::max(height(p->left), height(p->right));
}

template <class T>
int BinaryTree<T>::count_descendants(const TreeNode<T>* p) const {
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
void BinaryTree<T>::to_string(const TreeNode<T>* p, std::string& out) const {
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
const TreeNode<T>* BinaryTree<T>::nil() const {
    return nil_;
}

template <class T>
void BinaryTree<T>::set_nil(TreeNode<T>* nil_) {
    this->nil_ = nil_;
}

}

#endif
