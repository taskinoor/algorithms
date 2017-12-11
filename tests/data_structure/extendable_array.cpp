#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

#include "alg/common/randomizer.h"
#include "alg/data_structure/extendable_array.h"
#include "tests/helper.h"

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

TEST(ExtendableArray, CopyConstructor) {
    alg::ExtendableArray<int> a = {0, 1, 2, 3, 4};

    for (int i = 5; i < 10; i++) {
        a.append(i);
    }

    alg::ExtendableArray<int> b = a;

    for (int i = 0; i < 10; i++) {
        b[i]++;
    }

    ASSERT_EQ(10, a.count());
    ASSERT_EQ(10, b.count());

    for (int i = 0; i < 10; i++) {
        ASSERT_EQ(i, a[i]);
        ASSERT_EQ(i + 1, b[i]);
    }
}

TEST(ExtendableArray, MoveConstructor) {
    alg::ExtendableArray<std::string> a = {"foo"};
    alg::ExtendableArray<std::string> b = std::move(a);

    ASSERT_EQ(1, b.count());
    ASSERT_EQ("foo", b[0]);

    ASSERT_EQ(nullptr, a.data_ptr());
    ASSERT_EQ(0, a.count());
}

TEST(ExtendableArray, Capacity) {
    alg::ExtendableArray<int> a(1024);

    ASSERT_EQ(1024, a.capacity());
}

TEST(ExtendableArray, LargeRandomDataSet) {
    constexpr int total = 100000;
    constexpr int delete_freq = 10;

    std::vector<NoDefaultCtor<int>> std_vec;
    alg::ExtendableArray<NoDefaultCtor<int>> alg_arr;

    for (int i = 0; i < total; i++) {
        int data = alg::randomizer::uniform_int(-total, total);

        NoDefaultCtor<int> std_data(data);
        NoDefaultCtor<int> alg_data(data);

        std_vec.push_back(std_data);
        alg_arr.append(alg_data);

        if (!(i % delete_freq)) {
            int index = alg::randomizer::uniform_int(0, alg_arr.count() - 1);

            std_vec.erase(std_vec.begin() + index);
            alg_arr.remove(index);
        }
    }

    ASSERT_EQ(std_vec.size(), alg_arr.count());

    for (std::size_t i = 0; i < alg_arr.count(); i++) {
        ASSERT_EQ(std_vec[i].data(), alg_arr[i].data());
    }

    alg::ExtendableArray<NoDefaultCtor<int>> arr_copied = alg_arr;

    ASSERT_EQ(arr_copied.count(), alg_arr.count());

    for (std::size_t i = 0; i < arr_copied.count(); i++) {
        ASSERT_EQ(alg_arr[i], arr_copied[i]);
    }

    alg::ExtendableArray<NoDefaultCtor<int>> arr_moved = std::move(alg_arr);

    ASSERT_EQ(nullptr, alg_arr.data_ptr());
    ASSERT_EQ(0, alg_arr.count());
    ASSERT_EQ(0, alg_arr.capacity());

    ASSERT_EQ(arr_copied.count(), arr_moved.count());

    for (std::size_t i = 0; i < arr_copied.count(); i++) {
        ASSERT_EQ(arr_copied[i], arr_moved[i]);
    }
}

}
