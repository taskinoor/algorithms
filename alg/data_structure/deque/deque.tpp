namespace alg {

template <class T>
Deque<T>::Deque() {
    list = new LinkedList<T>();
    _count = 0;
}

template <class T>
Deque<T>::~Deque() {
    delete list;
}

template <class T>
void Deque<T>::push_back(T element) {
    list->insert_last(element);
    _count++;
}

template <class T>
void Deque<T>::push_front(T element) {
    list->insert_first(element);
    _count++;
}

template <class T>
ListNode<T> *Deque<T>::get_back_node() {
    ListNode<T> *node = list->last();

    if (!node) {
        throw DequeEmptyError();
    }

    return node;
}

template <class T>
ListNode<T> *Deque<T>::get_front_node() {
    ListNode<T> *node = list->first();

    if (!node) {
        throw DequeEmptyError();
    }

    return node;
}

template <class T>
T Deque<T>::pop_back() {
    ListNode<T> *node = get_back_node();
    T element = node->get_element();
    list->remove(node);
    _count--;

    return element;
}

template <class T>
T Deque<T>::pop_front() {
    ListNode<T> *node = get_front_node();
    T element = node->get_element();
    list->remove(node);
    _count--;

    return element;
}

template <class T>
T Deque<T>::back() {
    return get_back_node()->get_element();
}

template <class T>
T Deque<T>::front() {
    return get_front_node()->get_element();
}

template <class T>
size_t Deque<T>::count() {
    return _count;
}

}
