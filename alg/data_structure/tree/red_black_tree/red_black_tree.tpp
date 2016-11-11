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

}
