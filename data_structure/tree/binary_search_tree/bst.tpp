template <class T>
void BST<T>::insert(T element) {
    Node<T> *last = NULL;
    Node<T> *current = this->_root;
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
        this->_root = node;
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
    return search(this->_root, key);
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
    return min(this->_root);
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
    return max(this->_root);
}
