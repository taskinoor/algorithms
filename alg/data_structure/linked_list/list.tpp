namespace alg {

template <class T>
ListNode<T>::ListNode(T element) {
    prev = nullptr;
    next = nullptr;
    element_ = element;
}

template <class T>
T ListNode<T>::element() {
    return element_;
}

template <class T>
LinkedList<T>::LinkedList() {
    head = new ListNode<T>;
    tail = new ListNode<T>;

    head->next = tail;
    tail->prev = head;
}

template <class T>
LinkedList<T>::~LinkedList() {
    ListNode<T> *current = head->next;

    while (current != tail) {
        ListNode<T> *next = current->next;
        delete current;
        current = next;
    }

    delete head;
    delete tail;
}

template <class T>
ListNode<T> *LinkedList<T>::first() {
    return after(head);
}

template <class T>
ListNode<T> *LinkedList<T>::last() {
    return before(tail);
}

template <class T>
ListNode<T> *LinkedList<T>::after(ListNode<T> *p) {
    if (p->next == tail) {
        return nullptr;
    }

    return p->next;
}

template <class T>
ListNode<T> *LinkedList<T>::before(ListNode<T> *p) {
    if (p->prev == head) {
        return nullptr;
    }

    return p->prev;
}

template <class T>
void LinkedList<T>::insert_after(ListNode<T> *p, T element) {
    ListNode<T> *node = new ListNode<T>(element);

    node->next = p->next;
    node->prev = p;
    p->next->prev = node;
    p->next = node;
}

template <class T>
void LinkedList<T>::insert_before(ListNode<T> *p, T element) {
    ListNode<T> *node = new ListNode<T>(element);

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

template <class T>
ListNode<T> *LinkedList<T>::search(T element) {
    ListNode<T> *current = head->next;

    while (current != tail) {
        if (current->element() == element) {
            return current;
        }
        current = current->next;
    }

    return nullptr;
}

template <class T>
void LinkedList<T>::remove(ListNode<T> *p) {
    p->prev->next = p->next;
    p->next->prev = p->prev;

    delete p;
}

template <class T>
ListIterator<T> *LinkedList<T>::create_iterator(bool forward) {
    ListIterator<T> *iter;

    if (forward) {
        iter = new ForwardListIterator<T>(this);
    } else {
        iter = new BackwardListIterator<T>(this);
    }

    iter->first();

    return iter;
}

template <class T>
void LinkedList<T>::destroy_iterator(ListIterator<T> *iter) {
    delete iter;
}

template <class T>
ListIterator<T>::ListIterator(LinkedList<T> *list) {
    this->list = list;
    current = nullptr;
}

template <class T>
bool ListIterator<T>::is_done() const {
    return !current;
}

template <class T>
T ListIterator<T>::current_item() const {
    return current->element();
}

template <class T>
void ForwardListIterator<T>::first() {
    this->current = this->list->first();
}

template <class T>
void ForwardListIterator<T>::next() {
    this->current = this->list->after(this->current);
}

template <class T>
void BackwardListIterator<T>::first() {
    this->current = this->list->last();
}

template <class T>
void BackwardListIterator<T>::next() {
    this->current = this->list->before(this->current);
}

}