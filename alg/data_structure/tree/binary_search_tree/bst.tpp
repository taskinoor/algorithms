namespace alg {

template <class T>
void BST<T>::insert(T element) {
    TreeNode<T> *last = nullptr;
    TreeNode<T> *current = this->root();
    TreeNode<T> *node = new TreeNode<T>(element);

    while (current) {
        last = current;

        if (element < current->element()) {
            current = this->left(current);
        } else {
            current = this->right(current);
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
TreeNode<T> *BST<T>::search(TreeNode<T> *node, T key) {
    while (node && node->element() != key) {
        if (key < node->element()) {
             node = this->left(node);
        } else {
            node = this->right(node);
        }
    }

    return node;
}

template <class T>
TreeNode<T> *BST<T>::search(T key) {
    return search(this->root(), key);
}

template <class T>
TreeNode<T> *BST<T>::min(TreeNode<T> *node) {
    while (node && this->left(node)) {
        node = this->left(node);
    }

    return node;
}

template <class T>
TreeNode<T> *BST<T>::min() {
    return min(this->root());
}

template <class T>
TreeNode<T> *BST<T>::max(TreeNode<T> *node) {
    while (node && this->right(node)) {
        node = this->right(node);
    }

    return node;
}

template <class T>
TreeNode<T> *BST<T>::max() {
    return max(this->root());
}

template <class T>
TreeNode<T> *BST<T>::successor(TreeNode<T> *node) {
    if (this->right(node)) {
        return min(this->right(node));
    }

    TreeNode<T> *p = this->parent(node);

    while (p && this->right(p) == node) {
        node = p;
        p = this->parent(p);
    }

    return p;
}

template <class T>
TreeNode<T> *BST<T>::predecessor(TreeNode<T> *node) {
    if (this->left(node)) {
        return max(this->left(node));
    }

    TreeNode<T> *p = this->parent(node);

    while (p && this->left(p) == node) {
        node = p;
        p = this->parent(p);
    }

    return p;
}

template <class T>
void BST<T>::transplant(TreeNode<T> *u, TreeNode<T> *v) {
    TreeNode<T> *p = this->parent(u);

    if (!p) {
        this->set_root(v);
    } else {
        if (this->left(p) == u) {
            this->set_left(p, v);
        } else {
            this->set_right(p, v);
        }
    }
}

template <class T>
void BST<T>::remove(TreeNode<T> *z) {
    if (!this->left(z)) {
        transplant(z, this->right(z));
    } else if (!this->right(z)) {
        transplant(z, this->left(z));
    } else {
        TreeNode<T> *y = min(this->right(z));

        if (this->parent(y) != z) {
            transplant(y, this->right(y));
            this->set_right(y, this->right(z));
        }

        transplant(z, y);
        this->set_left(y, this->left(z));
    }

    this->set_left(z, nullptr);
    this->set_right(z, nullptr);

    delete z;
}

}
