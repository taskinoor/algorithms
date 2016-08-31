#include <gtest/gtest.h>

#include "binary_search.h"

TEST(BinarySearchTest, EmptyArray) {
    int a[] = {};

    ASSERT_EQ(-1, binary_search(a, 2, 0));
}

TEST(BinarySearchTest, NonEmptyArray) {
    int a[] = {2, 4, 5, 7, 8, 9, 12, 14, 17, 19, 22, 25, 27, 28, 33, 37};
    size_t n = 16;

    for (int i = 0; i < n; i++) {
        ASSERT_EQ(i, binary_search(a, a[i], n));
    }

    ASSERT_EQ(-1, binary_search(a, 0, n));
    ASSERT_EQ(-1, binary_search(a, 41, n));
    ASSERT_EQ(-1, binary_search(a, 10, n));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
