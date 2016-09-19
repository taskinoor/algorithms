#ifndef ALG_LINEAR_SEARCH_H_
#define ALG_LINEAR_SEARCH_H_

#include <cstddef>

namespace alg {

template <class T>
int linear_search(T *a, T key, std::size_t n);

}

#include "linear_search.tpp"

#endif
