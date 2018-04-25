#ifndef ALG_DNC_MAXIMUM_SUBARRAY_H_
#define ALG_DNC_MAXIMUM_SUBARRAY_H_

#include <limits>

namespace alg {
namespace dnc {

template <class T>
class MaxSubarrayResult {
public:
    int low;
    int high;
    T sum;
};

template <class T>
MaxSubarrayResult<T> max_crossing_subarray(T* a, int low, int mid, int high) {
    T left_max = std::numeric_limits<T>::lowest();
    int left_index = -1;
    T sum = T();

    for (int i = mid; i >= low; --i) {
        sum += a[i];

        if (sum > left_max) {
            left_max = sum;
            left_index = i;
        }
    }

    T right_max = std::numeric_limits<T>::lowest();
    int right_index = -1;
    sum = T();

    for (int i = mid + 1; i <= high; ++i) {
        sum += a[i];

        if (sum > right_max) {
            right_max = sum;
            right_index = i;
        }
    }

    return {left_index, right_index, left_max + right_max};
}

template <class T>
MaxSubarrayResult<T> max_subarray(T* a, int low, int high) {
    if (low == high) {
        return {low, low, a[low]};
    }

    int mid = (low + high) / 2;

    MaxSubarrayResult<T> left = max_subarray(a, low, mid);
    MaxSubarrayResult<T> right = max_subarray(a, mid + 1, high);
    MaxSubarrayResult<T> crossing = max_crossing_subarray(a, low, mid, high);

    if (left.sum >= right.sum && left.sum >= crossing.sum) {
        return left;
    } else if (right.sum >= left.sum && right.sum >= crossing.sum) {
        return right;
    } else {
        return crossing;
    }
}

}
}

#endif
