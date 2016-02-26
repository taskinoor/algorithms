#include <algorithm>

#include "subarray.h"

int max_subarray(int *a, size_t n) {
    if (!n) {
        return 0;
    }

    int *suffix_sum = new int[n];

    suffix_sum[0] = std::max(0, a[0]);

    for (int i = 1; i < n; i++) {
        suffix_sum[i] = std::max(0, suffix_sum[i - 1] + a[i]);
    }

    int max = suffix_sum[0];

    for (int i = 1; i < n; i++) {
        max = std::max(max, suffix_sum[i]);
    }

    delete[] suffix_sum;

    return max;
}
