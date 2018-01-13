#ifndef ALG_DP_MAXIMUM_SUBARRAY_H_
#define ALG_DP_MAXIMUM_SUBARRAY_H_

#include <cstddef>

#include <algorithm>

namespace alg {

template <class T>
T max_subarray_dp(T* a, std::size_t n) {
    if (!n) {
        return 0;
    }

    T* suffix_sum = new T[n];
    T zero = 0;

    suffix_sum[0] = std::max(zero, a[0]);

    for (int i = 1; i < n; i++) {
        suffix_sum[i] = std::max(zero, suffix_sum[i - 1] + a[i]);
    }

    T max_sum = suffix_sum[0];

    for (int i = 1; i < n; i++) {
        max_sum = std::max(max_sum, suffix_sum[i]);
    }

    delete[] suffix_sum;

    return max_sum;
}

}

#endif
