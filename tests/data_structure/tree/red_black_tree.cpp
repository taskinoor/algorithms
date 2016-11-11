#include <gtest/gtest.h>

#include "alg/data_structure/tree/red_black_tree/red_black_tree.h"

namespace algtest {

class RedBlackTree : public ::testing::Test {
protected:
    alg::RedBlackTree<int> *tree;

    virtual void SetUp() {
        tree = new alg::RedBlackTree<int>();
    }

    virtual void TearDown() {
        delete tree;
    }
};

TEST_F(RedBlackTree, RootColor) {
    alg::RBNode<int> *root = (alg::RBNode<int> *)tree->root();

    ASSERT_EQ(alg::BLACK, root->color());
}

TEST_F(RedBlackTree, LeafColor) {
    alg::RBNode<int> *nil = (alg::RBNode<int> *)tree->nil();

    ASSERT_EQ(alg::BLACK, nil->color());
}

TEST_F(RedBlackTree, Rotation) {
    constexpr int n = 6;
    int keys[n] = {7, 11, 9, 18, 14, 19};
    alg::TreeNode<int> *nodes[n];
    alg::TreeNode<int> *nil = tree->nil();

    for (int i = 0; i < n; i++) {
        nodes[i] = new alg::TreeNode<int>(keys[i], nil, nil, nil);
    }

    alg::TreeNode<int> *begin[n][3] = {
            nil, nil, nodes[1],
            nodes[0], nodes[2], nodes[3],
            nodes[1], nil, nil,
            nodes[1], nodes[4], nodes[5],
            nodes[3], nil, nil,
            nodes[3], nil, nil
    };
    alg::TreeNode<int> *after[n][3] = {
            nil, nil, nodes[3],
            nodes[3], nodes[2], nodes[4],
            nodes[1], nil, nil,
            nodes[0], nodes[1], nodes[5],
            nodes[1], nil, nil,
            nodes[3], nil, nil
    };

    for (int i = 0; i < n; i++) {
        tree->set_left(nodes[i], begin[i][1]);
        tree->set_right(nodes[i], begin[i][2]);
    }

    tree->rotate(nodes[1], true);

    for (int i = 0; i < n; i++) {
        ASSERT_EQ(keys[i], nodes[i]->element());
        ASSERT_EQ(after[i][0], tree->parent(nodes[i]));
        ASSERT_EQ(after[i][1], tree->left(nodes[i]));
        ASSERT_EQ(after[i][2], tree->right(nodes[i]));
    }

    tree->rotate(nodes[3], false);

    for (int i = 0; i < n; i++) {
        ASSERT_EQ(keys[i], nodes[i]->element());
        ASSERT_EQ(begin[i][0], tree->parent(nodes[i]));
        ASSERT_EQ(begin[i][1], tree->left(nodes[i]));
        ASSERT_EQ(begin[i][2], tree->right(nodes[i]));
    }

    for (int i = 0; i < n; i++) {
        delete nodes[i];
    }
}

}
