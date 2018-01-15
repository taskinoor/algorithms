#include <cstddef>

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

    for (int i = 0; i < 7; ++i) {
        ASSERT_EQ(expected[i], array[i]);
    }

    array[0] = 19;
    array[6] = 23;
    array[3] = 29;

    expected[0] = 19;
    expected[6] = 23;
    expected[3] = 29;

    for (int i = 0; i < 7; ++i) {
        ASSERT_EQ(expected[i], array[i]);
    }

    ASSERT_EQ(19, array.remove(0));
    ASSERT_EQ(7, array.remove(3));
    ASSERT_EQ(23, array.remove(4));

    ASSERT_EQ(4, array.count());

    int expected_after_remove[] = {17, 2, 29, 5};

    for (int i = 0; i < 4; ++i) {
        ASSERT_EQ(expected_after_remove[i], array[i]);
    }
}

TEST(ExtendableArray, Append) {
    alg::ExtendableArray<int> a;
    constexpr int n = 1000;

    for (int i = 0; i < n; ++i) {
        a.append(i);
        ASSERT_EQ(i + 1, a.count());
    }

    for (int i = 0; i < n; ++i) {
        ASSERT_EQ(i, a[i]);
    }
}

TEST(ExtendableArray, CopyConstructor) {
    alg::ExtendableArray<int> a = {0, 1, 2, 3, 4};

    for (int i = 5; i < 10; ++i) {
        a.append(i);
    }

    alg::ExtendableArray<int> b = a;

    for (int i = 0; i < 10; ++i) {
        ++b[i];
    }

    ASSERT_EQ(10, a.count());
    ASSERT_EQ(10, b.count());

    for (int i = 0; i < 10; ++i) {
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
    ASSERT_EQ(0, a.capacity());
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

    for (int i = 0; i < total; ++i) {
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

    for (std::size_t i = 0; i < alg_arr.count(); ++i) {
        ASSERT_EQ(std_vec[i].data(), alg_arr[i].data());
    }

    alg::ExtendableArray<NoDefaultCtor<int>> arr_copied = alg_arr;

    ASSERT_EQ(alg_arr.count(), arr_copied.count());

    for (std::size_t i = 0; i < arr_copied.count(); ++i) {
        ASSERT_EQ(alg_arr[i], arr_copied[i]);
    }

    alg::ExtendableArray<NoDefaultCtor<int>> arr_moved = std::move(alg_arr);

    ASSERT_EQ(nullptr, alg_arr.data_ptr());
    ASSERT_EQ(0, alg_arr.count());
    ASSERT_EQ(0, alg_arr.capacity());

    ASSERT_EQ(arr_copied.count(), arr_moved.count());

    for (std::size_t i = 0; i < arr_copied.count(); ++i) {
        ASSERT_EQ(arr_copied[i], arr_moved[i]);
    }
}

TEST(ExtendableArray, CopyAssignmentLargerThanCapacity) {
    alg::ExtendableArray<std::string> lhs = {"a"};
    alg::ExtendableArray<std::string> rhs = {"b", "c", "d", "e", "f", "g"};

    lhs = rhs;

    ASSERT_NE(rhs.data_ptr(), lhs.data_ptr());
    ASSERT_EQ(rhs.count(), lhs.count());
    ASSERT_EQ(rhs.count(), lhs.capacity());

    for (std::size_t i = 0; i < rhs.count(); ++i) {
        ASSERT_EQ(rhs[i], lhs[i]);
    }
}

TEST(ExtendableArray, CopyAssignmentSmallerThanCapacity) {
    alg::ExtendableArray<std::string> lhs = {"b", "c", "d", "e", "f", "g"};
    alg::ExtendableArray<std::string> rhs = {"a", "x", "y", "z"};

    lhs.append("h");

    ASSERT_EQ(12, lhs.capacity());

    lhs = rhs;

    ASSERT_NE(rhs.data_ptr(), lhs.data_ptr());
    ASSERT_EQ(rhs.count(), lhs.count());
    ASSERT_EQ(12, lhs.capacity());

    for (std::size_t i = 0; i < rhs.count(); ++i) {
        ASSERT_EQ(rhs[i], lhs[i]);
    }
}

TEST(ExtendableArray, CopyAssignmentEqualCapacity) {
    alg::ExtendableArray<std::string> lhs = {"b", "c", "d", "e", "f", "g"};
    alg::ExtendableArray<std::string> rhs = {"a", "x", "y", "z", "p", "q"};

    lhs = rhs;

    ASSERT_NE(rhs.data_ptr(), lhs.data_ptr());
    ASSERT_EQ(rhs.count(), lhs.count());
    ASSERT_EQ(rhs.capacity(), lhs.capacity());

    for (std::size_t i = 0; i < rhs.count(); ++i) {
        ASSERT_EQ(rhs[i], lhs[i]);
    }
}

TEST(ExtendableArray, SelfCopyAssignment) {
    alg::ExtendableArray<std::string> arr = {"a", "b", "c"};
    std::vector<std::string> expected = {"a", "b", "c"};

    arr = arr;

    ASSERT_NE(nullptr, arr.data_ptr());
    ASSERT_EQ(expected.size(), arr.count());

    for (std::size_t i = 0; i < expected.size(); ++i) {
        ASSERT_EQ(expected[i], arr[i]);
    }
}

TEST(ExtendableArray, CopyAssignmentRHSEmpty) {
    alg::ExtendableArray<std::string> lhs = {"a"};
    alg::ExtendableArray<std::string> rhs;

    lhs = rhs;

    ASSERT_EQ(0, lhs.count());
    ASSERT_NE(nullptr, lhs.data_ptr());
    ASSERT_EQ(1, lhs.capacity());
}

TEST(ExtendableArray, CopyAssignmentLHSEmpty) {
    alg::ExtendableArray<std::string> lhs;
    alg::ExtendableArray<std::string> rhs = {"a"};

    lhs = rhs;

    ASSERT_EQ(1, lhs.count());
    ASSERT_EQ("a", lhs[0]);
}

TEST(ExtendableArray, CopyAssignmentBothEmpty) {
    alg::ExtendableArray<std::string> lhs;
    alg::ExtendableArray<std::string> rhs;

    lhs = rhs;

    ASSERT_EQ(0, lhs.count());
    ASSERT_EQ(0, lhs.capacity());
    ASSERT_EQ(nullptr, lhs.data_ptr());
}

TEST(ExtendableArray, MoveAssignment) {
    constexpr int total = 10000;

    alg::ExtendableArray<NoDefaultCtor<int>> lhs;
    alg::ExtendableArray<NoDefaultCtor<int>> rhs;

    for (int i = 0; i < total; ++i) {
        rhs.append(NoDefaultCtor<int>{i});
    }

    std::size_t rhs_old_capacity = rhs.capacity();

    lhs = std::move(rhs);

    ASSERT_EQ(total, lhs.count());
    ASSERT_EQ(rhs_old_capacity, lhs.capacity());

    for (int i = 0; i < total; ++i) {
        ASSERT_EQ(i, lhs[i].data());
    }

    ASSERT_EQ(nullptr, rhs.data_ptr());
    ASSERT_EQ(0, rhs.capacity());
    ASSERT_EQ(0, rhs.count());
}

}
