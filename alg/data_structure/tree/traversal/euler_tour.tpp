namespace alg {

template <class T>
void visit(TreeNode<T> *v) {
    std::cout << v->get_element();
}

template <class T>
void euler_tour(BinaryTree<T> *tree) {
    euler_tour(tree, tree->root());
}

template <class T>
void euler_tour(BinaryTree<T> *tree, TreeNode<T> *v) {
    if (!v) {
        return;
    }

    visit(v);
    euler_tour(tree, tree->left(v));
    visit(v);
    euler_tour(tree, tree->right(v));
    visit(v);
}

}
