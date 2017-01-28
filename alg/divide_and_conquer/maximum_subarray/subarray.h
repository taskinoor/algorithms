#ifndef ALG_DNC_SUBARRAY_H_
#define ALG_DNC_SUBARRAY_H_

#include <limits>

namespace alg {

template <class T>
class MaxSubarrayResult {
public:
    int low;
    int high;
    T sum;
};

template <class T>
MaxSubarrayResult<T> max_crossing_subarray(T *a, int low, int mid, int high);

template <class T>
MaxSubarrayResult<T> max_subarray_dnc(T *a, int low, int high);

}

#include "subarray.tpp"

#endif
