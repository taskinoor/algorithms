namespace alg {

template <class T>
RBNode<T>::RBNode(RBColor color, T element, TreeNode<T> *parent,
        TreeNode<T> *left, TreeNode<T> *right) :
        TreeNode<T>(element, parent, left, right) {

    color_ = color;
}

template <class T>
RBColor RBNode<T>::color() {
    return color_;
}

template <class T>
RedBlackTree<T>::RedBlackTree() {
    this->set_nil(new RBNode<T>(BLACK));
    this->set_root(this->nil_);
}

template <class T>
void RedBlackTree<T>::rotate(TreeNode<T> *x, bool left) {
    TreeNode<T> *y = left ? this->right(x) : this->left(x);
    TreeNode<T> *p = this->parent(x);

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
    RBNode<T> *node = new RBNode<T>(RED, element,
            this->nil_, this->nil_, this->nil_);

    this->insert_node(node);
    insert_fixup(node);
}

template <class T>
void RedBlackTree<T>::insert_fixup(RBNode<T> *node) {
    while (true) {
        RBNode<T> *parent = (RBNode<T> *)this->parent(node);

        if (parent->color_ == BLACK) {
            break;
        }

        RBNode<T> *grandparent = (RBNode<T> *)this->parent(parent);
        bool left = this->left(grandparent) == parent;
        RBNode<T> *uncle = left ? (RBNode<T> *)this->right(grandparent) :
                (RBNode<T> *)this->left(grandparent);

        if (uncle->color_ == RED) {
            parent->color_ = BLACK;
            uncle->color_ = BLACK;
            grandparent->color_ = RED;

            node = grandparent;
        } else {
            bool rotation_needed =
                    (left ? this->right(parent) : this->left(parent)) == node;

            if (rotation_needed) {
                node = parent;
                rotate(node, left);
                parent = (RBNode<T> *)this->parent(node);
            }

            parent->color_ = BLACK;
            grandparent->color_ = RED;
            rotate(grandparent, !left);
        }
    }

    ((RBNode<T> *)this->root())->color_ = BLACK;
}

}
