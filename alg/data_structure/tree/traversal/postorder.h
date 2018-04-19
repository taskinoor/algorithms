#ifndef ALG_DS_TREE_TRAVERSAL_POSTORDER_H_
#define ALG_DS_TREE_TRAVERSAL_POSTORDER_H_

#include "alg/data_structure/tree/binary_tree.h"

namespace alg {
namespace ds {
namespace tree {
namespace traversal {

template <class OutputIt, class T>
OutputIt postorder(const BinaryTree<T>* tree, const Node<T>* v, OutputIt iter) {
    if (v == tree->nil()) {
        return iter;
    }

    iter = postorder(tree, tree->left(v), iter);
    iter = postorder(tree, tree->right(v), iter);

    *iter++ = v;

    return iter;
}

template <class OutputIt, class T>
OutputIt postorder(const BinaryTree<T>* tree, OutputIt iter) {
    return postorder(tree, tree->root(), iter);
}

}
}
}
}

#endif
