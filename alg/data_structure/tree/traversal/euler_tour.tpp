namespace alg {

template <class T>
void euler_visit(TreeNode<T> *v, std::string &out) {
    std::ostringstream buf;

    buf << v->element();
    out += buf.str();
}

template <class T>
std::string euler_tour(BinaryTree<T> *tree) {
    std::string out = "";
    euler_tour(tree, tree->root(), out);

    return out;
}

template <class T>
void euler_tour(BinaryTree<T> *tree, TreeNode<T> *v, std::string &out) {
    if (v == tree->nil()) {
        return;
    }

    euler_visit(v, out);
    euler_tour(tree, tree->left(v), out);
    euler_visit(v, out);
    euler_tour(tree, tree->right(v), out);
    euler_visit(v, out);
}

}
