template <class T>
Node<T>::Node(T element) {
    this->element = element;

    parent = NULL;
    left = NULL;
    right = NULL;
}

template <class T>
Node<T>::~Node() {
    delete left;
    delete right;
}

template <class T>
T Node<T>::get_element() {
    return element;
}

template <class T>
BinaryTree<T>::BinaryTree(Node<T> *root) {
    this->root = root;
}

template <class T>
BinaryTree<T>::~BinaryTree() {
    delete root;
}

template <class T>
Node<T> *BinaryTree<T>::get_root() {
    return root;
}

template <class T>
Node<T> *BinaryTree<T>::get_parent(Node<T> *p) {
    return p->parent;
}

template <class T>
Node<T> *BinaryTree<T>::get_child(Node<T> *p, bool is_right) {
    return is_right ? p->right : p->left;
}

template <class T>
void BinaryTree<T>::set_child(Node<T> *p, Node<T> *child, bool is_right) {
    child->parent = p;

    if (is_right) {
        p->right = child;
    } else {
        p->left = child;
    }
}

template <class T>
int BinaryTree<T>::depth(Node<T> *p) {
    int d = 0;

    while (p->parent != NULL) {
        p = p->parent;
        d++;
    }

    return d;
}

template <class T>
int BinaryTree<T>::height() {
    return height(root);
}

template <class T>
int BinaryTree<T>::height(Node<T> *p) {
    if (!p) {
        return -1;
    }

    return 1 + MAX(height(p->left), height(p->right));
}
