#include <array>
#include <gtest/gtest.h>

#include "alg/searching/range_query.h"

namespace algtest {

class RangeQuery : public ::testing::Test {
protected:
    alg::BST<int> *bst;

    virtual void SetUp() {
        bst = new alg::BST<int>();
        std::array<int, 14> elements = {
                68, 37, 99, 18, 55, 81, 12,
                23, 42, 61, 74, 90, 21, 49
        };

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

    alg::range_query(bst, 30, 80, result);

    ASSERT_EQ(expected, result);
}

TEST_F(RangeQuery, LeftOfRoot) {
    std::unordered_set<int> result;
    std::unordered_set<int> expected = {18, 12, 21};

    alg::range_query(bst, 12, 22, result);

    ASSERT_EQ(expected, result);
}

TEST_F(RangeQuery, RightOfRoot) {
    std::unordered_set<int> result;
    std::unordered_set<int> expected = {81};

    alg::range_query(bst, 80, 82, result);

    ASSERT_EQ(expected, result);
}

TEST_F(RangeQuery, MatchAll) {
    std::unordered_set<int> result;
    std::unordered_set<int> expected = {
            68, 37, 99, 18, 55, 81, 12,
            23, 42, 61, 74, 90, 21, 49
    };

    alg::range_query(bst, 0, 100, result);

    ASSERT_EQ(expected, result);
}

TEST_F(RangeQuery, MatchNone) {
    std::unordered_set<int> result;
    std::unordered_set<int> expected = {};

    alg::range_query(bst, 100, 110, result);

    ASSERT_EQ(expected, result);
}

}
