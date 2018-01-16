#include <list>

#include <gtest/gtest.h>

#include "alg/searching/linear_search.h"

namespace algtest {

TEST(LinearSearch, KeyExists) {
    constexpr int n = 11;
    int a[n] = {19, 11, 7, 3, 5, 23, 17, 29, 13, 2, 31};

    for (int i = 0; i < n; ++i) {
        ASSERT_EQ(a + i, alg::searching::linear_search(a, a + n, a[i]));
    }
}

TEST(LinearSearch, KeyDoesNotExists) {
    constexpr int n = 1;
    double a[n] = {1.618};

    ASSERT_EQ(a + n, alg::searching::linear_search(a, a + n, 3.14159));
}

TEST(LinearSearch, SearchWithSTLIterator) {
    std::list<int> lst = {2, 3, 5, 7, 11, 13, 17, 19, 23};

    for (const int value : lst) {
        auto it = alg::searching::linear_search(lst.begin(), lst.end(), value);

        ASSERT_EQ(value, *it);
    }

    ASSERT_EQ(lst.end(), alg::searching::linear_search(
            lst.begin(), lst.end(), 29));
}

}
