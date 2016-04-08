template <class T>
PreOrderIterator<T>::PreOrderIterator(BinaryTree<T> *tree) {
    this->tree = tree;
    stack = new Stack<Node<T> *>(256);
}

template <class T>
PreOrderIterator<T>::~PreOrderIterator() {
    delete stack;
}

template <class T>
void PreOrderIterator<T>::first() {
    stack->push(tree->root());
}

template <class T>
void PreOrderIterator<T>::next() {
    Node<T> *current = stack->pop();
    Node<T> *left = tree->left(current);
    Node<T> *right = tree->right(current);

    if (right) {
        stack->push(right);
    }
    if (left) {
        stack->push(left);
    }
}

template <class T>
bool PreOrderIterator<T>::is_done() const {
    return !stack->count();
}

template <class T>
T PreOrderIterator<T>::current_item() const {
    return stack->top()->get_element();
}
