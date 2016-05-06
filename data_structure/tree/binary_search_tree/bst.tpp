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
