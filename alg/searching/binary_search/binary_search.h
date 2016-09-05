#ifndef ALG_BINARY_SEARCH_H_
#define ALG_BINARY_SEARCH_H_

#include <cstddef>

namespace alg {

template <class T>
int binary_search(T *a, T key, std::size_t n);

}

#include "binary_search.tpp"

#endif
