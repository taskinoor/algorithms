namespace alg {

template <class T>
void range_query(BST<T> *bst, T k1, T k2, std::unordered_set<T> &result) {
    range_query(bst, bst->root(), k1, k2, result);
}

template <class T>
void range_query(BST<T> *bst, Node<T> *v, T k1, T k2, std::unordered_set<T> &result) {
    if (!v) {
        return;
    }

    if (v->get_element() < k1) {
        range_query(bst, bst->right(v), k1, k2, result);
    } else if (v->get_element() > k2) {
        range_query(bst, bst->left(v), k1, k2, result);
    } else {
        result.insert(v->get_element());

        range_query(bst, bst->left(v), k1, k2, result);
        range_query(bst, bst->right(v), k1, k2, result);
    }
}

}