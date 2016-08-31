#include <array>

#include <gtest/gtest.h>

#include "range_query.h"

class RangeQueryTest : public ::testing::Test {
protected:
    BST<int> *bst;

    virtual void SetUp() {
        bst = new BST<int>();
        std::array<int, 14> elements = {68, 37, 99, 18, 55, 81, 12, 23, 42, 61, 74, 90, 21, 49};

        for (int i = 0; i < elements.size(); i++) {
            bst->insert(elements[i]);
        }
    }

    virtual void TearDown() {
        delete bst;
    }
};

TEST_F(RangeQueryTest, IncludeRoot) {
    std::unordered_set<int> result;
    std::unordered_set<int> expected = {68, 37, 55, 42, 61, 49, 74};

    range_query(bst, 30, 80, result);

    ASSERT_EQ(expected, result);
}

TEST_F(RangeQueryTest, LeftOfRoot) {
    std::unordered_set<int> result;
    std::unordered_set<int> expected = {18, 12, 21};

    range_query(bst, 12, 22, result);

    ASSERT_EQ(expected, result);
}

TEST_F(RangeQueryTest, RightOfRoot) {
    std::unordered_set<int> result;
    std::unordered_set<int> expected = {81};

    range_query(bst, 80, 82, result);

    ASSERT_EQ(expected, result);
}

TEST_F(RangeQueryTest, MatchAll) {
    std::unordered_set<int> result;
    std::unordered_set<int> expected = {68, 37, 99, 18, 55, 81, 12, 23, 42, 61, 74, 90, 21, 49};

    range_query(bst, 0, 100, result);

    ASSERT_EQ(expected, result);
}

TEST_F(RangeQueryTest, MatchNone) {
    std::unordered_set<int> result;
    std::unordered_set<int> expected = {};

    range_query(bst, 100, 110, result);

    ASSERT_EQ(expected, result);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
