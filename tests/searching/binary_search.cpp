#include <cstddef>

#include <gtest/gtest.h>

#include "alg/searching/binary_search.h"

namespace algtest {

TEST(BinarySearch, EmptyArray) {
    int a[] = {};

    ASSERT_EQ(-1, alg::searching::binary_search(a, 2, 0));
}

TEST(BinarySearch, NonEmptyArray) {
    int a[] = {2, 4, 5, 7, 8, 9, 12, 14, 17, 19, 22, 25, 27, 28, 33, 37};
    std::size_t n = 16;

    for (unsigned int i = 0; i < n; ++i) {
        ASSERT_EQ(i, alg::searching::binary_search(a, a[i], n));
    }

    ASSERT_EQ(-1, alg::searching::binary_search(a, 0, n));
    ASSERT_EQ(-1, alg::searching::binary_search(a, 41, n));
    ASSERT_EQ(-1, alg::searching::binary_search(a, 10, n));
}

}
