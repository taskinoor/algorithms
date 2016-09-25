#include <gtest/gtest.h>
#include "subarray.h"

namespace algtest {

TEST(MaxSubarray, EmptyArray) {
    int a[] = {};

    ASSERT_EQ(0, alg::max_subarray(a, 0));
}

TEST(MaxSubarray, AllPositive) {
    double a[] = {2.2, 3.3, 5.5, 7.7};

    ASSERT_EQ(18.7, alg::max_subarray(a, 4));
}

TEST(MaxSubarray, AllNegative) {
    int a[] = {-2, -3, -5, -7};

    ASSERT_EQ(0, alg::max_subarray(a, 4));
}

TEST(MaxSubarray, AllZero) {
    int a[] = {0, 0, 0};

    ASSERT_EQ(0, alg::max_subarray(a, 3));
}

TEST(MaxSubarray, PositiveAndNegative) {
    int a[] = {-2, -4, 3, -1, 5, 6, -7, -2, 4, -3, 2};

    ASSERT_EQ(13, alg::max_subarray(a, 11));
}

}
