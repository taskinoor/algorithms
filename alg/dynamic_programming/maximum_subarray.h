#ifndef ALG_DP_MAXIMUM_SUBARRAY_H_
#define ALG_DP_MAXIMUM_SUBARRAY_H_

#include <cstddef>

#include <algorithm>

#include "alg/data_structure/extendable_array.h"

namespace alg {
namespace dp {

template <class T>
T max_subarray(T* a, std::size_t n) {
    if (!n) {
        return T();
    }

    ds::ExtendableArray<T> suffix_sum(n);

    suffix_sum[0] = std::max(T(), a[0]);

    for (std::size_t i = 1; i < n; ++i) {
        suffix_sum[i] = std::max(T(), suffix_sum[i - 1] + a[i]);
    }

    T max_sum = suffix_sum[0];

    for (std::size_t i = 1; i < n; ++i) {
        max_sum = std::max(max_sum, suffix_sum[i]);
    }

    return max_sum;
}

}
}

#endif
