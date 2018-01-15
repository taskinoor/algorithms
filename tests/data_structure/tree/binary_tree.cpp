#include <string>

#include <gtest/gtest.h>

#include "alg/data_structure/tree/binary_tree.h"

namespace algtest {

TEST(TreeNode, Default) {
    alg::TreeNode<int> n;

    ASSERT_EQ(0, n.element());
}

TEST(TreeNode, Element) {
    alg::TreeNode<int> n(2);

    ASSERT_EQ(2, n.element());
}

class BinaryTree : public ::testing::Test {
protected:
    alg::BinaryTree<int>* tree;
    alg::TreeNode<int>* node[6];

    virtual void SetUp() {
        for (int i = 0; i < 6; ++i) {
            node[i] = new alg::TreeNode<int>(i);
        }

        tree = new alg::BinaryTree<int>(node[0]);

        tree->set_left(node[0], node[1]);
        tree->set_right(node[0], node[2]);
        tree->set_left(node[1], node[3]);
        tree->set_right(node[1], node[4]);
        tree->set_right(node[4], node[5]);
    }

    virtual void TearDown() {
        delete tree;
    }
};

TEST_F(BinaryTree, Accessors) {
    alg::TreeNode<int>* expected[6][3] = {
        nullptr, node[1], node[2],
        node[0], node[3], node[4],
        node[0], nullptr, nullptr,
        node[1], nullptr, nullptr,
        node[1], nullptr, node[5],
        node[4], nullptr, nullptr
    };

    for (int i = 0; i < 6; ++i) {
        ASSERT_EQ(expected[i][0], tree->parent(node[i]));
        ASSERT_EQ(expected[i][1], tree->left(node[i]));
        ASSERT_EQ(expected[i][2], tree->right(node[i]));
    }
}

TEST_F(BinaryTree, Depth) {
    int expected[6] = {0, 1, 1, 2, 2, 3};

    for (int i = 0; i < 6; ++i) {
        ASSERT_EQ(expected[i], tree->depth(node[i]));
    }
}

TEST_F(BinaryTree, Height) {
    int expected[6] = {3, 2, 0, 0, 1, 0};

    for (int i = 0; i < 6; ++i) {
        ASSERT_EQ(expected[i], tree->height(node[i]));
    }

    ASSERT_EQ(3, tree->height());
}

TEST_F(BinaryTree, DescendantsCount) {
    int expected[6] = {6, 4, 1, 1, 2, 1};

    for (int i = 0; i < 6; ++i) {
        ASSERT_EQ(expected[i], tree->count_descendants(node[i]));
    }
}

TEST_F(BinaryTree, ToString) {
    std::string expected = "E: 0, L: 1, R: 2, P: nil\nE: 1, L: 3, R: 4, P: 0\nE: 3, L: nil, R: nil, P: 1\nE: 4, L: nil, R: 5, P: 1\nE: 5, L: nil, R: nil, P: 4\nE: 2, L: nil, R: nil, P: 0\n";

    ASSERT_EQ(expected, tree->to_string());
}

}
