#ifndef ALG_DP_SUBARRAY_H_
#define ALG_DP_SUBARRAY_H_

#include <cstddef>

#include "alg/common/utils.h"

namespace alg {

template <class T>
T max_subarray_dp(T *a, std::size_t n);

}

#include "subarray.tpp"

#endif
