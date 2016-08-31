namespace alg {

template <class T>
InOrderIterator<T>::InOrderIterator(BinaryTree<T> *tree) {
    this->tree = tree;
    stack = new Stack<TreeNode<T> *>(256);
}

template <class T>
InOrderIterator<T>::~InOrderIterator() {
    delete stack;
}

template <class T>
void InOrderIterator<T>::push_left_nodes(TreeNode<T> *p) {
    while (p) {
        stack->push(p);
        p = tree->left(p);
    }
}

template <class T>
void InOrderIterator<T>::first() {
    push_left_nodes(tree->root());
}

template <class T>
void InOrderIterator<T>::next() {
    TreeNode<T> *p = stack->pop();
    push_left_nodes(tree->right(p));
}

template <class T>
bool InOrderIterator<T>::is_done() const {
    return !stack->count();
}

template <class T>
T InOrderIterator<T>::current_item() const {
    return stack->top()->get_element();
}

}
