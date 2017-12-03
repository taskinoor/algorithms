#include <gtest/gtest.h>

#include "alg/dynamic_programming/maximum_subarray.h"

namespace algtest {

TEST(MaxSubarrayDP, EmptyArray) {
    int a[] = {};

    ASSERT_EQ(0, alg::max_subarray_dp(a, 0));
}

TEST(MaxSubarrayDP, AllPositive) {
    double a[] = {2.2, 3.3, 5.5, 7.7};

    ASSERT_EQ(18.7, alg::max_subarray_dp(a, 4));
}

/*
 * Behavior for this all negative case is different from
 * divide and conquer implementation.
 */
TEST(MaxSubarrayDP, AllNegative) {
    int a[] = {-2, -3, -5, -7};

    ASSERT_EQ(0, alg::max_subarray_dp(a, 4));
}

TEST(MaxSubarrayDP, AllZero) {
    int a[] = {0, 0, 0};

    ASSERT_EQ(0, alg::max_subarray_dp(a, 3));
}

TEST(MaxSubarrayDP, PositiveAndNegative) {
    int a1[] = {-2, -4, 3, -1, 5, 6, -7, -2, 4, -3, 2};
    int a2[] = {
        13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7
    };

    ASSERT_EQ(13, alg::max_subarray_dp(a1, 11));
    ASSERT_EQ(43, alg::max_subarray_dp(a2, 16));
}

}
