#include <gtest/gtest.h>

#include "binary_tree.h"

TEST(NodeTest, DefaultElement) {
    Node<int> n;

    ASSERT_EQ(0, n.get_element());
}

TEST(NodeTest, GetElement) {
    Node<int> n(2);

    ASSERT_EQ(2, n.get_element());
}

class BinaryTreeTest : public ::testing::Test {
protected:
    BinaryTree<int> *tree;
    Node<int> *node[6];

    virtual void SetUp() {
        for (int i = 0; i < 6; i++) {
            node[i] = new Node<int>(i);
        }
        tree = new BinaryTree<int>(node[0]);

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

TEST_F(BinaryTreeTest, AccessorMethods) {
    Node<int> *expected[6][3] = {
        NULL, node[1], node[2],
        node[0], node[3], node[4],
        node[0], NULL, NULL,
        node[1], NULL, NULL,
        node[1], NULL, node[5],
        node[4], NULL, NULL
    };

    for (int i = 0; i < 6; i++) {
        ASSERT_EQ(expected[i][0], tree->parent(node[i]));
        ASSERT_EQ(expected[i][1], tree->left(node[i]));
        ASSERT_EQ(expected[i][2], tree->right(node[i]));
    }
}

TEST_F(BinaryTreeTest, Depth) {
    int expected[6] = {0, 1, 1, 2, 2, 3};

    for (int i = 0; i < 6; i++) {
        ASSERT_EQ(expected[i], tree->depth(node[i]));
    }
}

TEST_F(BinaryTreeTest, Height) {
    int expected[6] = {3, 2, 0, 0, 1, 0};

    for (int i = 0; i < 6; i++) {
        ASSERT_EQ(expected[i], tree->height(node[i]));
    }

    ASSERT_EQ(3, tree->height());
}

TEST_F(BinaryTreeTest, CountDescendants) {
    int expected[6] = {6, 4, 1, 1, 2, 1};

    for (int i = 0; i < 6; i++) {
        ASSERT_EQ(expected[i], tree->count_descendants(node[i]));
    }
}

TEST_F(BinaryTreeTest, Print) {
    testing::internal::CaptureStdout();

    tree->print();

    ASSERT_STREQ("node: 0, left: 1, right: 2, parent: null\nnode: 1, left: 3, right: 4, parent: 0\nnode: 3, left: null, right: null, parent: 1\nnode: 4, left: null, right: 5, parent: 1\nnode: 5, left: null, right: null, parent: 4\nnode: 2, left: null, right: null, parent: 0\n", testing::internal::GetCapturedStdout().c_str());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
