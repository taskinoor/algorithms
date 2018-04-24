#ifndef ALG_DS_TREE_TRAVERSAL_EULER_TOUR_H_
#define ALG_DS_TREE_TRAVERSAL_EULER_TOUR_H_

#include "alg/data_structure/tree/binary_tree.h"

namespace alg {
namespace ds {
namespace tree {
namespace traversal {

template <class OutputIt, class T>
OutputIt euler_tour(const BinaryTree<T>* tree, const Node<T>* v, OutputIt iter) {
    if (v == tree->nil()) {
        return iter;
    }

    *iter++ = v;
    iter = euler_tour(tree, tree->left(v), iter);

    *iter++ = v;
    iter = euler_tour(tree, tree->right(v), iter);

    *iter++ = v;

    return iter;
}

template <class OutputIt, class T>
OutputIt euler_tour(const BinaryTree<T>* tree, OutputIt iter) {
    return euler_tour(tree, tree->root(), iter);
}

}
}
}
}

#endif
