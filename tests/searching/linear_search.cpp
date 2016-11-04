#include <gtest/gtest.h>

#include "alg/searching/linear_search/linear_search.h"

namespace algtest {

TEST(LinearSearch, KeyExists) {
    constexpr int n = 11;
    int a[n] = {19, 11, 7, 3, 5, 23, 17, 29, 13, 2, 31};

    for (int i = 0; i < n; i++) {
        ASSERT_EQ(i, alg::linear_search(a, a[i], n));
    }
}

TEST(LinearSearch, KeyDoesNotExists) {
    constexpr int n = 1;
    double a[n] = {1.618};

    ASSERT_EQ(-1, alg::linear_search(a, 3.14159, n));
}

}
