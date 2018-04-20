#include <cstddef>

#include <array>

#include <gtest/gtest.h>

#include "alg/data_structure/tree/binary_search_tree.h"
#include "alg/data_structure/tree/binary_tree.h"
#include "alg/data_structure/tree/traversal/euler_tour.h"
#include "alg/data_structure/tree/traversal/inorder.h"
#include "alg/data_structure/tree/traversal/postorder.h"
#include "alg/data_structure/tree/traversal/preorder.h"

namespace algtest {

class TreeTraversal : public ::testing::Test {
protected:
    alg::ds::tree::BinarySearchTree<char>* tree;
    alg::ds::tree::BinarySearchTree<char>* tree_only_root;
    alg::ds::tree::Node<char>* node[9];

    virtual void SetUp() {
        tree = new alg::ds::tree::BinarySearchTree<char>();

        for (int i = 0; i < 9; ++i) {
            node[i] = new alg::ds::tree::Node<char>('A' + i,
                    tree->nil(), tree->nil(), tree->nil());
        }

        tree->set_root(node[index('F')]);

        int child_map[9][2] = {
            -1, -1,
            'A', 'D',
            -1, -1,
            'C', 'E',
            -1, -1,
            'B', 'G',
            -1, 'I',
            -1, -1,
            'H', -1
        };

        for (int i = 0; i < 9; ++i) {
            if (child_map[i][0] != -1) {
                tree->set_left(node[i], node[index(child_map[i][0])]);
            }

            if (child_map[i][1] != -1) {
                tree->set_right(node[i], node[index(child_map[i][1])]);
            }
        }

        tree_only_root = new alg::ds::tree::BinarySearchTree<char>();

        tree_only_root->set_root(new alg::ds::tree::Node<char>('A',
                tree_only_root->nil(), tree_only_root->nil(),
                tree_only_root->nil()));
    }

    virtual void TearDown() {
        delete tree;
        delete tree_only_root;
    }

private:
    int index(char ch) {
        return ch - 'A';
    }
};

TEST_F(TreeTraversal, PreOrder) {
    std::array<char, 9> expected = {'F', 'B', 'A', 'D', 'C', 'E', 'G', 'I', 'H'};
    std::array<const alg::ds::tree::Node<char>*, 9> result;

    auto iter = alg::ds::tree::traversal::preorder(tree, result.begin());

    for (std::size_t i = 0; i < 9; ++i) {
        ASSERT_EQ(expected[i], result[i]->element());
    }

    ASSERT_EQ(result.end(), iter);
}

TEST_F(TreeTraversal, PreOrderOnlyRoot) {
    std::array<const alg::ds::tree::Node<char>*, 1> result;

    auto iter = alg::ds::tree::traversal::preorder(
            tree_only_root, result.begin());

    ASSERT_EQ('A', result[0]->element());
    ASSERT_EQ(result.end(), iter);
}

TEST_F(TreeTraversal, PostOrder) {
    std::array<char, 9> expected = {'A', 'C', 'E', 'D', 'B', 'H', 'I', 'G', 'F'};
    std::array<const alg::ds::tree::Node<char>*, 9> result;

    auto iter = alg::ds::tree::traversal::postorder(tree, result.begin());

    for (std::size_t i = 0; i < 9; ++i) {
        ASSERT_EQ(expected[i], result[i]->element());
    }

    ASSERT_EQ(result.end(), iter);
}

TEST_F(TreeTraversal, PostOrderOnlyRoot) {
    std::array<const alg::ds::tree::Node<char>*, 1> result;

    auto iter = alg::ds::tree::traversal::postorder(
            tree_only_root, result.begin());

    ASSERT_EQ('A', result[0]->element());
    ASSERT_EQ(result.end(), iter);
}

TEST_F(TreeTraversal, InOrder) {
    std::array<char, 9> expected = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
    std::array<const alg::ds::tree::Node<char>*, 9> result;

    auto iter = alg::ds::tree::traversal::inorder(tree, result.begin());

    for (std::size_t i = 0; i < 9; ++i) {
        ASSERT_EQ(expected[i], result[i]->element());
    }

    ASSERT_EQ(result.end(), iter);
}

TEST_F(TreeTraversal, InOrderOnlyRoot) {
    std::array<const alg::ds::tree::Node<char>*, 1> result;

    auto iter = alg::ds::tree::traversal::inorder(
            tree_only_root, result.begin());

    ASSERT_EQ('A', result[0]->element());
    ASSERT_EQ(result.end(), iter);
}

TEST_F(TreeTraversal, EulerTour) {
    ASSERT_EQ("FBAAABDCCCDEEEDBFGGIHHHIIGF",
            alg::ds::tree::traversal::euler_tour(tree));
}

TEST_F(TreeTraversal, EulerTourOnlyRoot) {
    ASSERT_EQ("AAA", alg::ds::tree::traversal::euler_tour(tree_only_root));
}

}
