#include <gtest/gtest.h>

#include "euler_tour.h"
#include "inorder.h"
#include "postorder.h"
#include "preorder.h"

namespace algtest {

class TreeTraversal : public ::testing::Test {
private:
    int index(char ch) {
        return ch - 'A';
    }

protected:
    alg::BinaryTree<char> *tree;
    alg::BinaryTree<char> *tree_only_root;
    alg::TreeNode<char> *node[9];

    virtual void SetUp() {
        for (int i = 0; i < 9; i++) {
            node[i] = new alg::TreeNode<char>('A' + i);
        }

        tree = new alg::BinaryTree<char>(node[index('F')]);
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

        for (int i = 0; i < 9; i++) {
            if (child_map[i][0] != -1) {
                tree->set_left(node[i], node[index(child_map[i][0])]);
            }

            if (child_map[i][1] != -1) {
                tree->set_right(node[i], node[index(child_map[i][1])]);
            }
        }

        tree_only_root = new alg::BinaryTree<char>(new alg::TreeNode<char>('A'));
    }

    virtual void TearDown() {
        delete tree;
        delete tree_only_root;
    }
};

TEST_F(TreeTraversal, PreOrder) {
    alg::PreOrderIterator<char> *it = new alg::PreOrderIterator<char>(tree);
    char expected[9] = {'F', 'B', 'A', 'D', 'C', 'E', 'G', 'I', 'H'};
    int i = 0;

    for (it->first(); !it->is_done(); it->next(), i++) {
        ASSERT_EQ(expected[i], it->current_item());
    }
    ASSERT_EQ(9, i);

    delete it;
}

TEST_F(TreeTraversal, PreOrderOnlyRoot) {
    alg::PreOrderIterator<char> *it =
            new alg::PreOrderIterator<char>(tree_only_root);
    int i = 0;

    for (it->first(); !it->is_done(); it->next(), i++) {
        ASSERT_EQ('A', it->current_item());
    }
    ASSERT_EQ(1, i);

    delete it;
}

TEST_F(TreeTraversal, PostOrder) {
    alg::PostOrderIterator<char> *it = new alg::PostOrderIterator<char>(tree);
    char expected[9] = {'A', 'C', 'E', 'D', 'B', 'H', 'I', 'G', 'F'};
    int i = 0;

    for (it->first(); !it->is_done(); it->next(), i++) {
        ASSERT_EQ(expected[i], it->current_item());
    }
    ASSERT_EQ(9, i);

    delete it;
}

TEST_F(TreeTraversal, PostOrderOnlyRoot) {
    alg::PostOrderIterator<char> *it =
            new alg::PostOrderIterator<char>(tree_only_root);
    int i = 0;

    for (it->first(); !it->is_done(); it->next(), i++) {
        ASSERT_EQ('A', it->current_item());
    }
    ASSERT_EQ(1, i);

    delete it;
}

TEST_F(TreeTraversal, InOrder) {
    alg::InOrderIterator<char> *it = new alg::InOrderIterator<char>(tree);
    char expected[9] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
    int i = 0;

    for (it->first(); !it->is_done(); it->next(), i++) {
        ASSERT_EQ(expected[i], it->current_item());
    }
    ASSERT_EQ(9, i);

    delete it;
}

TEST_F(TreeTraversal, InOrderOnlyRoot) {
    alg::InOrderIterator<char> *it =
            new alg::InOrderIterator<char>(tree_only_root);
    int i = 0;

    for (it->first(); !it->is_done(); it->next(), i++) {
        ASSERT_EQ('A', it->current_item());
    }
    ASSERT_EQ(1, i);

    delete it;
}

TEST_F(TreeTraversal, EulerTour) {
    testing::internal::CaptureStdout();

    alg::euler_tour(tree);

    ASSERT_STREQ("FBAAABDCCCDEEEDBFGGIHHHIIGF",
            testing::internal::GetCapturedStdout().c_str());
}

TEST_F(TreeTraversal, EulerTourOnlyRoot) {
    testing::internal::CaptureStdout();

    alg::euler_tour(tree_only_root);

    ASSERT_STREQ("AAA", testing::internal::GetCapturedStdout().c_str());
}

}
