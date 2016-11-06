namespace alg {

template <class T>
PostOrderIterator<T>::PostOrderIterator(BinaryTree<T> *tree) {
    this->tree = tree;
    stack = new Stack<TreeNode<T> *>(256);
}

template <class T>
PostOrderIterator<T>::~PostOrderIterator() {
    delete stack;
}

template <class T>
void PostOrderIterator<T>::first() {
    stack->push(tree->root());
    last_visited = tree->nil();

    next();
}

template <class T>
void PostOrderIterator<T>::next() {
    TreeNode<T> *nil_ = tree->nil();

    if (!stack->count()) {
        last_visited = nil_;
        return;
    }

    TreeNode<T> *node = stack->top();

    while (true) {
        if (tree->right(node) == last_visited && last_visited != nil_) {
            break;
        }

        if (tree->left(node) == last_visited && tree->right(node) == nil_) {
            break;
        }

        while (tree->left(node) != nil_ && tree->left(node) != last_visited) {
            node = tree->left(node);
            stack->push(node);
        }

        if (tree->right(node) != nil_) {
            node = tree->right(node);
            stack->push(node);
        }

        if (tree->left(node) == nil_ && tree->right(node) == nil_) {
            break;
        }
    }

    last_visited = stack->pop();
}

template <class T>
bool PostOrderIterator<T>::is_done() const {
    return last_visited == tree->nil();
}

template <class T>
T PostOrderIterator<T>::current_item() const {
    return last_visited->element();
}

}
