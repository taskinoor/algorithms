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
