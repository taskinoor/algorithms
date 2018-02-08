#include <gtest/gtest.h>

#include "alg/data_structure/tree/binary_tree.h"
#include "alg/data_structure/tree/bst.h"
#include "alg/data_structure/tree/traversal/euler_tour.h"
#include "alg/data_structure/tree/traversal/inorder.h"
#include "alg/data_structure/tree/traversal/postorder.h"
#include "alg/data_structure/tree/traversal/preorder.h"

namespace algtest {

class TreeTraversal : public ::testing::Test {
protected:
    alg::BST<char>* tree;
    alg::BST<char>* tree_only_root;
    alg::TreeNode<char>* node[9];

    virtual void SetUp() {
        tree = new alg::BST<char>();

        for (int i = 0; i < 9; ++i) {
            node[i] = new alg::TreeNode<char>('A' + i,
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

        tree_only_root = new alg::BST<char>();
        tree_only_root->set_root(new alg::TreeNode<char>('A',
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
    alg::ds::PreOrderIterator<char>* it =
            new alg::ds::PreOrderIterator<char>(tree);

    char expected[9] = {'F', 'B', 'A', 'D', 'C', 'E', 'G', 'I', 'H'};
    int i = 0;

    for (it->first(); !it->is_done(); it->next(), ++i) {
        ASSERT_EQ(expected[i], it->current_item());
    }
    ASSERT_EQ(9, i);

    delete it;
}

TEST_F(TreeTraversal, PreOrderOnlyRoot) {
    alg::ds::PreOrderIterator<char>* it =
            new alg::ds::PreOrderIterator<char>(tree_only_root);

    int i = 0;

    for (it->first(); !it->is_done(); it->next(), ++i) {
        ASSERT_EQ('A', it->current_item());
    }
    ASSERT_EQ(1, i);

    delete it;
}

TEST_F(TreeTraversal, PostOrder) {
    alg::ds::PostOrderIterator<char>* it =
            new alg::ds::PostOrderIterator<char>(tree);

    char expected[9] = {'A', 'C', 'E', 'D', 'B', 'H', 'I', 'G', 'F'};
    int i = 0;

    for (it->first(); !it->is_done(); it->next(), ++i) {
        ASSERT_EQ(expected[i], it->current_item());
    }
    ASSERT_EQ(9, i);

    delete it;
}

TEST_F(TreeTraversal, PostOrderOnlyRoot) {
    alg::ds::PostOrderIterator<char>* it =
            new alg::ds::PostOrderIterator<char>(tree_only_root);

    int i = 0;

    for (it->first(); !it->is_done(); it->next(), ++i) {
        ASSERT_EQ('A', it->current_item());
    }
    ASSERT_EQ(1, i);

    delete it;
}

TEST_F(TreeTraversal, InOrder) {
    alg::ds::InOrderIterator<char>* it =
            new alg::ds::InOrderIterator<char>(tree);

    char expected[9] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
    int i = 0;

    for (it->first(); !it->is_done(); it->next(), ++i) {
        ASSERT_EQ(expected[i], it->current_item());
    }
    ASSERT_EQ(9, i);

    delete it;
}

TEST_F(TreeTraversal, InOrderOnlyRoot) {
    alg::ds::InOrderIterator<char>* it =
            new alg::ds::InOrderIterator<char>(tree_only_root);

    int i = 0;

    for (it->first(); !it->is_done(); it->next(), ++i) {
        ASSERT_EQ('A', it->current_item());
    }
    ASSERT_EQ(1, i);

    delete it;
}

TEST_F(TreeTraversal, EulerTour) {
    ASSERT_EQ("FBAAABDCCCDEEEDBFGGIHHHIIGF", alg::euler_tour(tree));
}

TEST_F(TreeTraversal, EulerTourOnlyRoot) {
    ASSERT_EQ("AAA", alg::euler_tour(tree_only_root));
}

}
