#ifndef ALG_RANGE_QUERY_H_
#define ALG_RANGE_QUERY_H_

#include <unordered_set>

#include "bst.h"

namespace alg {

template <class T>
void range_query(BST<T> *bst, T k1, T k2, std::unordered_set<T> &result);

template <class T>
void range_query(BST<T> *bst, Node<T> *v, T k1, T k2, std::unordered_set<T> &result);

}

#include "range_query.tpp"

#endif
