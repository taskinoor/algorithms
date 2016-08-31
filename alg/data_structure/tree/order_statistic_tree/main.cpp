#include <array>

#include <gtest/gtest.h>

#include "order_statistic_tree.h"

class OSTTest : public ::testing::Test {
protected:
    OrderStatisticTree<int> *ost;
    std::array<int, 14> elements;
    std::array<int, 7> after_remove;

    virtual void SetUp() {
        ost = new OrderStatisticTree<int>();
        elements = {44, 23, 63, 17, 33, 51, 74, 8, 20, 48, 58, 71, 46, 72};

        for (int i = 0; i < elements.size(); i++) {
            ost->insert(elements[i]);
        }
    }

    virtual void TearDown() {
        delete ost;
    }

    void remove_nodes() {
        std::array<int, 7> to_remove = {63, 48, 8, 17, 71, 23, 44};

        for (int i = 0; i < to_remove.size(); i++) {
            ost->remove(ost->search(to_remove[i]));
        }

        after_remove = {33, 51, 74, 20, 58, 46, 72};
    }
};

TEST_F(OSTTest, NodeCountAfterInsert) {
    std::array<int, 14> expected = {14, 5, 8, 3, 1, 4, 3, 1, 1, 2, 1, 2, 1, 1};
    std::array<int, 14> result;

    for (int i = 0; i < elements.size(); i++) {
        result[i] = ((OSTNode<int> *)ost->search(elements[i]))->get_count();
    }

    ASSERT_EQ(expected, result);
}

TEST_F(OSTTest, NodeCountAfterRemove) {
    remove_nodes();

    std::array<int, 7> expected = {2, 2, 1, 1, 1, 7, 4};
    std::array<int, 7> result;

    for (int i = 0; i < after_remove.size(); i++) {
        result[i] = ((OSTNode<int> *)ost->search(after_remove[i]))->get_count();
    }

    ASSERT_EQ(expected, result);
}

TEST_F(OSTTest, SelectAfterInsert) {
    std::array<int, 14> expected = {8, 17, 20, 23, 33, 44, 46, 48, 51, 58, 63, 71, 72, 74};
    std::array<int, 14> result;

    for (int i = 0; i < elements.size(); i++) {
        result[i] = ost->select(i);
    }

    ASSERT_EQ(expected, result);
}

TEST_F(OSTTest, SelectAfterRemove) {
    remove_nodes();

    std::array<int, 7> expected = {20, 33, 46, 51, 58, 72, 74};
    std::array<int, 7> result;

    for (int i = 0; i < after_remove.size(); i++) {
        result[i] = ost->select(i);
    }

    ASSERT_EQ(expected, result);
}

TEST_F(OSTTest, RankAfterInsert) {
    std::array<int, 14> expected = {5, 3, 10, 1, 4, 8, 13, 0, 2, 7, 9, 11, 6, 12};
    std::array<int, 14> result;

    for (int i = 0; i < elements.size(); i++) {
        result[i] = ost->rank(elements[i]);
    }

    ASSERT_EQ(expected, result);
}

TEST_F(OSTTest, RankAfterRemove) {
    remove_nodes();

    std::array<int, 7> expected = {1, 3, 6, 0, 4, 2, 5};
    std::array<int, 7> result;

    for (int i = 0; i < after_remove.size(); i++) {
        result[i] = ost->rank(after_remove[i]);
    }

    ASSERT_EQ(expected, result);
}

TEST_F(OSTTest, RankInvalidItem) {
    ASSERT_EQ(-1, ost->rank(129));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
