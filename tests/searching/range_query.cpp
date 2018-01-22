#include <algorithm>
#include <array>
#include <iterator>
#include <unordered_set>

#include <gtest/gtest.h>

#include "alg/searching/range_query.h"

namespace algtest {

class RangeQuery : public ::testing::Test {
protected:
    alg::BST<int>* bst;
    std::array<int, 14> elements;

    virtual void SetUp() {
        elements = {68, 37, 99, 18, 55, 81, 12, 23, 42, 61, 74, 90, 21, 49};
        bst = new alg::BST<int>();

        for (const auto& e : elements) {
            bst->insert(e);
        }
    }

    virtual void TearDown() {
        delete bst;
    }
};

TEST_F(RangeQuery, IncludeRoot) {
    std::unordered_set<int> result;
    std::unordered_set<int> expected = {68, 37, 55, 42, 61, 49, 74};

    alg::searching::range_query(bst, 30, 80, std::inserter(result, result.end()));

    ASSERT_EQ(expected, result);
}

TEST_F(RangeQuery, LeftOfRoot) {
    std::unordered_set<int> result;
    std::unordered_set<int> expected = {18, 12, 21};

    alg::searching::range_query(bst, 12, 22, std::inserter(result, result.end()));

    ASSERT_EQ(expected, result);
}

TEST_F(RangeQuery, RightOfRoot) {
    std::unordered_set<int> result;
    std::unordered_set<int> expected = {81};

    alg::searching::range_query(bst, 80, 82, std::inserter(result, result.end()));

    ASSERT_EQ(expected, result);
}

TEST_F(RangeQuery, MatchAll) {
    std::array<int, 14> result;

    alg::searching::range_query(bst, 0, 100, result.begin());

    std::sort(elements.begin(), elements.end());
    std::sort(result.begin(), result.end());

    ASSERT_EQ(elements, result);
}

TEST_F(RangeQuery, MatchNone) {
    std::array<int, 0> result;

    auto iter = alg::searching::range_query(bst, 100, 110, result.begin());

    ASSERT_EQ(result.begin(), iter);
}

}
