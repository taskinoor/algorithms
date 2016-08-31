namespace alg {

template <class T>
TreeNode<T>::TreeNode(T element) {
    this->element = element;

    parent = NULL;
    left = NULL;
    right = NULL;
}

template <class T>
TreeNode<T>::~TreeNode() {
    delete left;
    delete right;
}

template <class T>
T TreeNode<T>::get_element() {
    return element;
}

template <class T>
BinaryTree<T>::BinaryTree(TreeNode<T> *root) {
   _root = root;
}

template <class T>
BinaryTree<T>::~BinaryTree() {
    delete _root;
}

template <class T>
TreeNode<T> *BinaryTree<T>::root() {
    return _root;
}

template <class T>
TreeNode<T> *BinaryTree<T>::parent(TreeNode<T> *p) {
    return p->parent;
}

template <class T>
TreeNode<T> *BinaryTree<T>::left(TreeNode<T> *p) {
    return p->left;
}

template <class T>
TreeNode<T> *BinaryTree<T>::right(TreeNode<T> *p) {
    return p->right;
}

template <class T>
void BinaryTree<T>::set_root(TreeNode<T> *r) {
    _root = r;
    r->parent = NULL;
}

template <class T>
void BinaryTree<T>::set_left(TreeNode<T> *p, TreeNode<T> *child) {
    if (child) {
        child->parent = p;
    }
    p->left = child;
}

template <class T>
void BinaryTree<T>::set_right(TreeNode<T> *p, TreeNode<T> *child) {
    if (child) {
        child->parent = p;
    }
    p->right = child;
}

template <class T>
int BinaryTree<T>::depth(TreeNode<T> *p) {
    int d = 0;

    while (p->parent != NULL) {
        p = p->parent;
        d++;
    }

    return d;
}

template <class T>
int BinaryTree<T>::height() {
    return height(_root);
}

template <class T>
int BinaryTree<T>::height(TreeNode<T> *p) {
    if (!p) {
        return -1;
    }

    return 1 + MAX(height(p->left), height(p->right));
}

template <class T>
int BinaryTree<T>::count_descendants(TreeNode<T> *p) {
    if (!p) {
        return 0;
    }

    return 1 + count_descendants(p->left) + count_descendants(p->right);
}

template <class T>
void BinaryTree<T>::print() {
    print(_root);
}

template <class T>
void BinaryTree<T>::print(TreeNode<T> *p) {
    if (!p) {
        return;
    }

    std::cout << "node: " << p->element;
    if (p->left) {
        std::cout << ", left: " << p->left->element;
    } else {
        std::cout << ", left: null";
    }
    if (p->right) {
        std::cout << ", right: " << p->right->element;
    } else {
        std::cout << ", right: null";
    }
    if (p->parent) {
        std::cout << ", parent: " << p->parent->element;
    } else {
        std::cout << ", parent: null";
    }
    std::cout << std::endl;

    print(p->left);
    print(p->right);
}

}
