template <class T>
void BST<T>::insert(T element) {
    Node<T> *last = NULL;
    Node<T> *current = this->root();
    Node<T> *node = new Node<T>(element);

    while (current) {
        last = current;

        if (element < current->get_element()) {
            current = left(current);
        } else {
            current = right(current);
        }
    }

    if (!last) {
        set_root(node);
    } else if (element < last->get_element()) {
        set_left(last, node);
    } else {
        set_right(last, node);
    }
}

template <class T>
Node<T> *BST<T>::search(Node<T> *node, T key) {
    while (node && node->get_element() != key) {
        if (key < node->get_element()) {
             node = left(node);
        } else {
            node = right(node);
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
    while (node && left(node)) {
        node = left(node);
    }

    return node;
}

template <class T>
Node<T> *BST<T>::min() {
    return min(this->root());
}

template <class T>
Node<T> *BST<T>::max(Node<T> *node) {
    while (node && right(node)) {
        node = right(node);
    }

    return node;
}

template <class T>
Node<T> *BST<T>::max() {
    return max(this->root());
}

template <class T>
Node<T> *BST<T>::successor(Node<T> *node) {
    if (right(node)) {
        return min(right(node));
    }

    Node<T> *p = parent(node);

    while (p && right(p) == node) {
        node = p;
        p = parent(p);
    }

    return p;
}

template <class T>
Node<T> *BST<T>::predecessor(Node<T> *node) {
    if (left(node)) {
        return max(left(node));
    }

    Node<T> *p = parent(node);

    while (p && left(p) == node) {
        node = p;
        p = parent(p);
    }

    return p;
}

template <class T>
void BST<T>::transplant(Node<T> *u, Node<T> *v) {
    Node<T> *p = parent(u);

    if (!p) {
        set_root(v);
    } else {
        if (left(p) == u) {
            set_left(p, v);
        } else {
            set_right(p, v);
        }
    }
}

template <class T>
void BST<T>::remove(Node<T> *z) {
    if (!left(z)) {
        transplant(z, right(z));
    } else if (!right(z)) {
        transplant(z, left(z));
    } else {
        Node<T> *y = min(right(z));

        if (parent(y) != z) {
            transplant(y, right(y));
            set_right(y, right(z));
        }

        transplant(z, y);
        set_left(y, left(z));
    }

    set_left(z, NULL);
    set_right(z, NULL);
    delete z;
}
