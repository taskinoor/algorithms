#include <string>
#include <stdexcept>
#include <utility>

#include <gtest/gtest.h>

#include "alg/data_structure/extendable_array.h"

namespace algtest {

TEST(ExtendableArray, InvalidIndex) {
    alg::ExtendableArray<int> array;

    ASSERT_THROW(array[-1], std::out_of_range);
    ASSERT_THROW(array[0], std::out_of_range);

    ASSERT_THROW(array.add(-1, 2), std::out_of_range);
    ASSERT_THROW(array.add(1, 2), std::out_of_range);

    ASSERT_THROW(array[-1] = 2, std::out_of_range);
    ASSERT_THROW(array[0] = 2, std::out_of_range);

    ASSERT_THROW(array.remove(-1), std::out_of_range);
    ASSERT_THROW(array.remove(0), std::out_of_range);
}

TEST(ExtendableArray, Operations) {
    alg::ExtendableArray<int> array;

    array.add(0, 2);
    array.add(1, 3);
    array.add(2, 5);
    array.add(2, 7);
    array.add(0, 11);
    array.add(5, 13);
    array.add(1, 17);

    ASSERT_EQ(7, array.count());

    int expected[] = {11, 17, 2, 3, 7, 5, 13};

    for (int i = 0; i < 7; i++) {
        ASSERT_EQ(expected[i], array[i]);
    }

    array[0] = 19;
    array[6] = 23;
    array[3] = 29;

    expected[0] = 19;
    expected[6] = 23;
    expected[3] = 29;

    for (int i = 0; i < 7; i++) {
        ASSERT_EQ(expected[i], array[i]);
    }

    ASSERT_EQ(19, array.remove(0));
    ASSERT_EQ(7, array.remove(3));
    ASSERT_EQ(23, array.remove(4));

    ASSERT_EQ(4, array.count());

    int expected_after_remove[] = {17, 2, 29, 5};

    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(expected_after_remove[i], array[i]);
    }
}

TEST(ExtendableArray, Append) {
    alg::ExtendableArray<int> a;
    constexpr int n = 1000;

    for (int i = 0; i < n; i++) {
        a.append(i);
        ASSERT_EQ(i + 1, a.count());
    }

    for (int i = 0; i < n; i++) {
        ASSERT_EQ(i, a[i]);
    }
}

TEST(ExtendableArray, Copy) {
    alg::ExtendableArray<int> a = {0, 1, 2, 3, 4};

    for (int i = 5; i < 10; i++) {
        a.append(i);
    }

    alg::ExtendableArray<int> b = a;

    for (int i = 0; i < 10; i++) {
        b[i]++;
    }

    for (int i = 0; i < 10; i++) {
        ASSERT_EQ(i, a[i]);
        ASSERT_EQ(i + 1, b[i]);
    }
}

TEST(ExtendableArray, Move) {
    alg::ExtendableArray<std::string> a = {"foo"};
    alg::ExtendableArray<std::string> b = std::move(a);

    ASSERT_EQ(1, b.count());
    ASSERT_EQ("foo", b[0]);
}

}
