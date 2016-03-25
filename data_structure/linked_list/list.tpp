template <class T>
Node<T>::Node(T element) {
    prev = NULL;
    next = NULL;
    this->element = element;
}

template <class T>
T Node<T>::get_element() {
    return element;
}
