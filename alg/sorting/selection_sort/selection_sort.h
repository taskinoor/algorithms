#ifndef ALG_SELECTION_SORT_H_
#define ALG_SELECTION_SORT_H_

#include <cstddef>
#include "utils.h"

namespace alg {

template <class T>
void selection_sort(T *a, std::size_t n);

}

#include "selection_sort.tpp"

#endif
