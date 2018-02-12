#include <gtest/gtest.h>

#include "alg/divide_and_conquer/maximum_subarray.h"

namespace algtest {

TEST(MaxSubarrayDNC, AllPositive) {
    double a[] = {2.2, 3.3, 5.5, 7.7};

    alg::dnc::MaxSubarrayResult<double> res = alg::dnc::max_subarray(a, 0, 3);

    ASSERT_EQ(18.7, res.sum);
    ASSERT_EQ(0, res.low);
    ASSERT_EQ(3, res.high);
}

/*
 * Behavior for this all negative case is different from
 * dynamic programming implementation.
 */
TEST(MaxSubarrayDNC, AllNegative) {
    int a[] = {-2, -3, -5, -7};

    alg::dnc::MaxSubarrayResult<int> res = alg::dnc::max_subarray(a, 0, 3);

    ASSERT_EQ(-2, res.sum);
    ASSERT_EQ(0, res.low);
    ASSERT_EQ(0, res.high);
}

TEST(MaxSubarrayDNC, AllZero) {
    int a[] = {0, 0, 0};

    alg::dnc::MaxSubarrayResult<int> res = alg::dnc::max_subarray(a, 0, 2);

    ASSERT_EQ(0, res.sum);
}

TEST(MaxSubarrayDNC, PositiveAndNegative) {
    int a1[] = {-2, -4, 3, -1, 5, 6, -7, -2, 4, -3, 2};
    int a2[] = {
        13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7
    };

    alg::dnc::MaxSubarrayResult<int> res_1 = alg::dnc::max_subarray(a1, 0, 10);
    alg::dnc::MaxSubarrayResult<int> res_2 = alg::dnc::max_subarray(a2, 0, 15);

    ASSERT_EQ(13, res_1.sum);
    ASSERT_EQ(2, res_1.low);
    ASSERT_EQ(5, res_1.high);

    ASSERT_EQ(43, res_2.sum);
    ASSERT_EQ(7, res_2.low);
    ASSERT_EQ(10, res_2.high);
}

}
