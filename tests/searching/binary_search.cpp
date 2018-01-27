#include <array>

#include <gtest/gtest.h>

#include "alg/searching/binary_search.h"

namespace algtest {

TEST(BinarySearch, EmptyArray) {
    std::array<int, 0> data;

    auto iter = alg::searching::binary_search(data.begin(), data.end(), 2);

    ASSERT_EQ(data.end(), iter);
}

TEST(BinarySearch, NonEmptyArray) {
    using alg::searching::binary_search;

    std::array<int, 16> data = {2, 4, 5, 7, 8, 9, 12, 14, 17, 19, 22, 25,
            27, 28, 33, 37};

    for (const int& key : data) {
        ASSERT_EQ(key, *binary_search(data.begin(), data.end(), key));
    }

    ASSERT_EQ(data.end(), binary_search(data.begin(), data.end(), 0));
    ASSERT_EQ(data.end(), binary_search(data.begin(), data.end(), 41));
    ASSERT_EQ(data.end(), binary_search(data.begin(), data.end(), 10));
}

TEST(BinarySearch, SingleElement) {
    using alg::searching::binary_search;

    std::array<int, 1> data = {2};

    auto iter = binary_search(data.begin(), data.end(), 2);

    ASSERT_EQ(data.begin(), iter);
    ASSERT_EQ(2, *iter);

    for (int key : {1, 3}) {
        ASSERT_EQ(data.end(), binary_search(data.begin(), data.end(), key));
    }
}

}
