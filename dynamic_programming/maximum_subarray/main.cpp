#include <gtest/gtest.h>

#include "subarray.h"

TEST(MaxSubarrayTest, EmptyArray) {
    int a[] = {};

    ASSERT_EQ(0, max_subarray(a, 0));
}

TEST(MaxSubarrayTest, AllPositive) {
    int a[] = {2, 3, 5, 7};

    ASSERT_EQ(17, max_subarray(a, 4));
}

TEST(MaxSubarrayTest, AllNegative) {
    int a[] = {-2, -3, -5, -7};

    ASSERT_EQ(0, max_subarray(a, 4));
}

TEST(MaxSubarrayTest, AllZero) {
    int a[] = {0, 0, 0};

    ASSERT_EQ(0, max_subarray(a, 3));
}

TEST(MaxSubarrayTest, PositiveAndNegative) {
    int a[] = {-2, -4, 3, -1, 5, 6, -7, -2, 4, -3, 2};

    ASSERT_EQ(13, max_subarray(a, 11));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
