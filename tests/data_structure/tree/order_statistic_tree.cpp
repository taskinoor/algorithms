#include <array>
#include <gtest/gtest.h>
#include "order_statistic_tree.h"

namespace algtest {

class OST : public ::testing::Test {
protected:
    alg::OrderStatisticTree<int> *ost;
    std::array<int, 14> elements;
    std::array<int, 7> after_remove;

    virtual void SetUp() {
        ost = new alg::OrderStatisticTree<int>();
        elements = {44, 23, 63, 17, 33, 51, 74, 8, 20, 48, 58, 71, 46, 72};

        for (const auto& e : elements) {
            ost->insert(e);
        }
    }

    virtual void TearDown() {
        delete ost;
    }

    void remove_nodes() {
        std::array<int, 7> to_remove = {63, 48, 8, 17, 71, 23, 44};

        for (const auto& r : to_remove) {
            ost->remove(ost->search(r));
        }

        after_remove = {33, 51, 74, 20, 58, 46, 72};
    }
};

TEST_F(OST, NodeCountAfterInsert) {
    std::array<int, 14> expected = {14, 5, 8, 3, 1, 4, 3, 1, 1, 2, 1, 2, 1, 1};
    std::array<int, 14> result;

    for (unsigned int i = 0; i < elements.size(); i++) {
        result[i] = ((alg::OSTNode<int> *)ost->search(elements[i]))->count();
    }

    ASSERT_EQ(expected, result);
}

TEST_F(OST, NodeCountAfterRemove) {
    remove_nodes();

    std::array<int, 7> expected = {2, 2, 1, 1, 1, 7, 4};
    std::array<int, 7> result;

    for (unsigned int i = 0; i < after_remove.size(); i++) {
        result[i] = ((alg::OSTNode<int> *)ost->search(after_remove[i]))->count();
    }

    ASSERT_EQ(expected, result);
}

TEST_F(OST, SelectAfterInsert) {
    std::array<int, 14> expected = {
            8, 17, 20, 23, 33, 44, 46,
            48, 51, 58, 63, 71, 72, 74
    };
    std::array<int, 14> result;

    for (unsigned int i = 0; i < elements.size(); i++) {
        result[i] = ost->select(i);
    }

    ASSERT_EQ(expected, result);
}

TEST_F(OST, SelectAfterRemove) {
    remove_nodes();

    std::array<int, 7> expected = {20, 33, 46, 51, 58, 72, 74};
    std::array<int, 7> result;

    for (unsigned int i = 0; i < after_remove.size(); i++) {
        result[i] = ost->select(i);
    }

    ASSERT_EQ(expected, result);
}

TEST_F(OST, RankAfterInsert) {
    std::array<int, 14> expected = {
            5, 3, 10, 1, 4, 8, 13, 0, 2, 7, 9, 11, 6, 12
    };
    std::array<int, 14> result;

    for (unsigned int i = 0; i < elements.size(); i++) {
        result[i] = ost->rank(elements[i]);
    }

    ASSERT_EQ(expected, result);
}

TEST_F(OST, RankAfterRemove) {
    remove_nodes();

    std::array<int, 7> expected = {1, 3, 6, 0, 4, 2, 5};
    std::array<int, 7> result;

    for (unsigned int i = 0; i < after_remove.size(); i++) {
        result[i] = ost->rank(after_remove[i]);
    }

    ASSERT_EQ(expected, result);
}

TEST_F(OST, RankInvalidItem) {
    ASSERT_EQ(-1, ost->rank(129));
}

}
