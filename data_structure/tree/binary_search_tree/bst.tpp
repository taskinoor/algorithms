template <class T>
void BST<T>::insert(T element) {
    Node<T> *last = NULL;
    Node<T> *current = this->root();
    Node<T> *node = new Node<T>(element);

    while (current) {
        last = current;

        if (element < current->get_element()) {
            current = this->left(current);
        } else {
            current = this->right(current);
        }
    }

    if (!last) {
        this->set_root(node);
    } else if (element < last->get_element()) {
        this->set_left(last, node);
    } else {
        this->set_right(last, node);
    }
}

template <class T>
Node<T> *BST<T>::search(Node<T> *node, T key) {
    while (node && node->get_element() != key) {
        if (key < node->get_element()) {
             node = this->left(node);
        } else {
            node = this->right(node);
        }
    }

    return node;
}

template <class T>
Node<T> *BST<T>::search(T key) {
    return search(this->root(), key);
}

template <class T>
Node<T> *BST<T>::min(Node<T> *node) {
    while (node && this->left(node)) {
        node = this->left(node);
    }

    return node;
}

template <class T>
Node<T> *BST<T>::min() {
    return min(this->root());
}

template <class T>
Node<T> *BST<T>::max(Node<T> *node) {
    while (node && this->right(node)) {
        node = this->right(node);
    }

    return node;
}

template <class T>
Node<T> *BST<T>::max() {
    return max(this->root());
}

template <class T>
Node<T> *BST<T>::successor(Node<T> *node) {
    if (this->right(node)) {
        return min(this->right(node));
    }

    Node<T> *p = this->parent(node);

    while (p && this->right(p) == node) {
        node = p;
        p = this->parent(p);
    }

    return p;
}

template <class T>
Node<T> *BST<T>::predecessor(Node<T> *node) {
    if (this->left(node)) {
        return max(this->left(node));
    }

    Node<T> *p = this->parent(node);

    while (p && this->left(p) == node) {
        node = p;
        p = this->parent(p);
    }

    return p;
}

template <class T>
void BST<T>::transplant(Node<T> *u, Node<T> *v) {
    Node<T> *p = this->parent(u);

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
void BST<T>::remove(Node<T> *z) {
    if (!this->left(z)) {
        transplant(z, this->right(z));
    } else if (!this->right(z)) {
        transplant(z, this->left(z));
    } else {
        Node<T> *y = min(this->right(z));

        if (this->parent(y) != z) {
            transplant(y, this->right(y));
            this->set_right(y, this->right(z));
        }

        transplant(z, y);
        this->set_left(y, this->left(z));
    }

    this->set_left(z, NULL);
    this->set_right(z, NULL);

    delete z;
}
