#include <array>

#include <gtest/gtest.h>

#include "alg/common/randomizer.h"
#include "alg/data_structure/heap/binary/binary_heap.h"

namespace algtest {

TEST(BinaryHeap, Parent) {
    int expected[] = {-1, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7};

    for (int i = 0; i <= 16; i++) {
        ASSERT_EQ(expected[i], alg::heap::binary::parent(i));
    }
}

TEST(BinaryHeap, Left) {
    int expected[] = {1, 3, 5, 7, 9, 11, 13, 15};

    for (int i = 0; i <= 7; i++) {
        ASSERT_EQ(expected[i], alg::heap::binary::left(i));
    }
}

TEST(BinaryHeap, Right) {
    int expected[] = {2, 4, 6, 8, 10, 12, 14, 16};

    for (int i = 0; i <= 7; i++) {
        ASSERT_EQ(expected[i], alg::heap::binary::right(i));
    }
}

TEST(BinaryHeap, BuildMaxHeap) {
    std::array<int, 10> data = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    std::array<int, 10> expected = {16, 14, 10, 8, 7, 9, 3, 2, 4, 1};

    alg::heap::binary::build_heap(data.data(), data.size(),
            alg::heap::binary::MAX_HEAP);

    ASSERT_EQ(expected, data);
}

TEST(BinaryHeap, BuildMinHeap) {
    std::array<int, 10> data = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    std::array<int, 10> expected = {1, 2, 3, 4, 7, 9, 10, 14, 8, 16};

    alg::heap::binary::build_heap(data.data(), data.size(),
            alg::heap::binary::MIN_HEAP);

    ASSERT_EQ(expected, data);
}

TEST(BinaryHeap, BuildMaxHeapLargeData) {
    std::array<double, 8191> data;

    for (std::size_t i = 0; i < data.size(); i++) {
        data[i] = alg::randomizer::uniform_double(-131071, 131071);
    }

    alg::heap::binary::build_heap(data.data(), data.size(),
            alg::heap::binary::MAX_HEAP);

    for (std::size_t i = data.size() - 1; i > 0; i--) {
        ASSERT_GE(data[(i - 1) / 2], data[i]);
    }
}

TEST(BinaryHeap, BuildMinHeapLargeData) {
    std::array<double, 8191> data;

    for (std::size_t i = 0; i < data.size(); i++) {
        data[i] = alg::randomizer::uniform_double(-131071, 131071);
    }

    alg::heap::binary::build_heap(data.data(), data.size(),
            alg::heap::binary::MIN_HEAP);

    for (std::size_t i = data.size() - 1; i > 0; i--) {
        ASSERT_LE(data[(i - 1) / 2], data[i]);
    }
}

}
