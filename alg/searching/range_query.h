#ifndef ALG_SEARCHING_RANGE_QUERY_H_
#define ALG_SEARCHING_RANGE_QUERY_H_

#include "alg/data_structure/tree/binary_tree.h"
#include "alg/data_structure/tree/bst.h"

namespace alg {
namespace searching {

template <class OutputIt, class T>
OutputIt range_query(const BST<T>* bst, const TreeNode<T>* v, const T& k1,
        const T& k2, OutputIt iter) {

    if (v == bst->nil()) {
        return iter;
    }

    if (v->element() < k1) {
        iter = range_query(bst, bst->right(v), k1, k2, iter);
    } else if (v->element() > k2) {
        iter = range_query(bst, bst->left(v), k1, k2, iter);
    } else {
        *iter++ = v->element();

        iter = range_query(bst, bst->left(v), k1, k2, iter);
        iter = range_query(bst, bst->right(v), k1, k2, iter);
    }

    return iter;
}

template <class OutputIt, class T>
OutputIt range_query(const BST<T>* bst, const T& k1, const T& k2,
        OutputIt iter) {

    return range_query(bst, bst->root(), k1, k2, iter);
}

}
}

#endif
