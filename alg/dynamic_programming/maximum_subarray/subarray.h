#ifndef ALG_SUBARRAY_H_
#define ALG_SUBARRAY_H_

#include <cstddef>
#include "utils.h"

namespace alg {

template <class T>
T max_subarray(T *a, std::size_t n);

}

#include "subarray.tpp"

#endif
