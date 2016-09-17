#ifndef ALG_INSERTION_SORT_H_
#define ALG_INSERTION_SORT_H_

#include <cstddef>

namespace alg {

template <class T>
void insertion_sort(T *a, std::size_t n);

}

#include "insertion_sort.tpp"

#endif
