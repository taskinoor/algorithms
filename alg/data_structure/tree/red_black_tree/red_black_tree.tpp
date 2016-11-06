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

}
