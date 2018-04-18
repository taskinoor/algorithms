#ifndef ALG_DS_TREE_TRAVERSAL_PREORDER_H_
#define ALG_DS_TREE_TRAVERSAL_PREORDER_H_

#include "alg/data_structure/tree/binary_tree.h"

namespace alg {
namespace ds {
namespace tree {
namespace traversal {

template <class OutputIt, class T>
OutputIt preorder(const BinaryTree<T>* tree, const Node<T>* v, OutputIt iter) {
    if (v == tree->nil()) {
        return iter;
    }

    *iter++ = v;

    iter = preorder(tree, tree->left(v), iter);
    iter = preorder(tree, tree->right(v), iter);

    return iter;
}

template <class OutputIt, class T>
OutputIt preorder(const BinaryTree<T>* tree, OutputIt iter) {
    return preorder(tree, tree->root(), iter);
}

}
}
}
}

#endif
