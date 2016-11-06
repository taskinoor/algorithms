namespace alg {

template <class T>
TreeNode<T>::TreeNode(T element, TreeNode<T> *parent, TreeNode<T> *left,
        TreeNode<T> *right) {

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
BinaryTree<T>::BinaryTree(TreeNode<T> *root) {
   root_ = root;
   nil_ = nullptr;
}

template <class T>
BinaryTree<T>::~BinaryTree() {
    free(root_);
    delete nil_;
}

template <class T>
void BinaryTree<T>::free(TreeNode<T> *node) {
    if (node == nil_) {
        return;
    }

    free(node->left);
    free(node->right);

    delete node;
}

template <class T>
TreeNode<T> *BinaryTree<T>::root() {
    return root_;
}

template <class T>
TreeNode<T> *BinaryTree<T>::parent(TreeNode<T> *p) {
    return p->parent;
}

template <class T>
TreeNode<T> *BinaryTree<T>::left(TreeNode<T> *p) {
    return p->left;
}

template <class T>
TreeNode<T> *BinaryTree<T>::right(TreeNode<T> *p) {
    return p->right;
}

template <class T>
void BinaryTree<T>::set_root(TreeNode<T> *r) {
    root_ = r;

    if (root_ != nil_) {
        root_->parent = nil_;
    }
}

template <class T>
void BinaryTree<T>::set_left(TreeNode<T> *p, TreeNode<T> *child) {
    if (child != nil_) {
        child->parent = p;
    }

    p->left = child;
}

template <class T>
void BinaryTree<T>::set_right(TreeNode<T> *p, TreeNode<T> *child) {
    if (child != nil_) {
        child->parent = p;
    }

    p->right = child;
}

template <class T>
int BinaryTree<T>::depth(TreeNode<T> *p) {
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
int BinaryTree<T>::height(TreeNode<T> *p) {
    if (p == nil_) {
        return -1;
    }

    return 1 + max(height(p->left), height(p->right));
}

template <class T>
int BinaryTree<T>::count_descendants(TreeNode<T> *p) {
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
void BinaryTree<T>::to_string(TreeNode<T> *p, std::string& out) {
    if (p == nil_) {
        return;
    }

    std::ostringstream buf;

    buf << "node: " << p->element();

    if (p->left != nil_) {
        buf << ", left: " << p->left->element();
    } else {
        buf << ", left: null";
    }

    if (p->right != nil_) {
        buf << ", right: " << p->right->element();
    } else {
        buf << ", right: null";
    }

    if (p->parent != nil_) {
        buf << ", parent: " << p->parent->element();
    } else {
        buf << ", parent: null";
    }

    buf << std::endl;

    out += buf.str();

    to_string(p->left, out);
    to_string(p->right, out);
}

template <class T>
TreeNode<T> *BinaryTree<T>::nil() {
    return nil_;
}

template <class T>
void BinaryTree<T>::set_nil(TreeNode<T> *nil_) {
    this->nil_ = nil_;
}

}
