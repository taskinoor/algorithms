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

template <class T>
LinkedList<T>::LinkedList() {
    head = new Node<T>;
    tail = new Node<T>;

    head->next = tail;
    tail->prev = head;
}

template <class T>
LinkedList<T>::~LinkedList() {
    Node<T> *current = head->next;

    while (current != tail) {
        Node<T> *next = current->next;
        delete current;
        current = next;
    }

    delete head;
    delete tail;
}

template <class T>
Node<T> *LinkedList<T>::first() {
    return after(head);
}

template <class T>
Node<T> *LinkedList<T>::last() {
    return before(tail);
}

template <class T>
Node<T> *LinkedList<T>::after(Node<T> *p) {
    if (p->next == tail) {
        return NULL;
    }

    return p->next;
}

template <class T>
Node<T> *LinkedList<T>::before(Node<T> *p) {
    if (p->prev == head) {
        return NULL;
    }

    return p->prev;
}

template <class T>
void LinkedList<T>::insert_after(Node<T> *p, T element) {
    Node<T> *node = new Node<T>(element);

    node->next = p->next;
    node->prev = p;
    p->next->prev = node;
    p->next = node;
}

template <class T>
void LinkedList<T>::insert_before(Node<T> *p, T element) {
    Node<T> *node = new Node<T>(element);

    node->next = p;
    node->prev = p->prev;
    p->prev->next = node;
    p->prev = node;
}

template <class T>
void LinkedList<T>::insert_first(T element) {
    insert_after(head, element);
}

template <class T>
void LinkedList<T>::insert_last(T element) {
    insert_before(tail, element);
}
