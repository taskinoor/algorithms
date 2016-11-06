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

}
