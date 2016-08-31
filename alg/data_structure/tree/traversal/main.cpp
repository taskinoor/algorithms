#include <gtest/gtest.h>

#include "preorder.h"
#include "postorder.h"
#include "inorder.h"
#include "euler_tour.h"

class TreeTraversalTest : public ::testing::Test {
private:
    int index(char ch) {
        return ch - 'A';
    }
protected:
    BinaryTree<char> *tree;
    BinaryTree<char> *tree_only_root;
    Node<char> *node[9];

    virtual void SetUp() {
        for (int i = 0; i < 9; i++) {
            node[i] = new Node<char>('A' + i);
        }
        tree = new BinaryTree<char>(node[index('F')]);
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

        tree_only_root = new BinaryTree<char>(new Node<char>('A'));
    }

    virtual void TearDown() {
        delete tree;
        delete tree_only_root;
    }
};

TEST_F(TreeTraversalTest, PreOrder) {
    PreOrderIterator<char> *it = new PreOrderIterator<char>(tree);
    char expected[9] = {'F', 'B', 'A', 'D', 'C', 'E', 'G', 'I', 'H'};
    int i = 0;

    for (it->first(); !it->is_done(); it->next(), i++) {
        ASSERT_EQ(expected[i], it->current_item());
    }
    ASSERT_EQ(9, i);

    delete it;
}

TEST_F(TreeTraversalTest, PreOrderOnlyRoot) {
    PreOrderIterator<char> *it = new PreOrderIterator<char>(tree_only_root);
    int i = 0;

    for (it->first(); !it->is_done(); it->next(), i++) {
        ASSERT_EQ('A', it->current_item());
    }
    ASSERT_EQ(1, i);

    delete it;
}

TEST_F(TreeTraversalTest, PostOrder) {
    PostOrderIterator<char> *it = new PostOrderIterator<char>(tree);
    char expected[9] = {'A', 'C', 'E', 'D', 'B', 'H', 'I', 'G', 'F'};
    int i = 0;

    for (it->first(); !it->is_done(); it->next(), i++) {
        ASSERT_EQ(expected[i], it->current_item());
    }
    ASSERT_EQ(9, i);

    delete it;
}

TEST_F(TreeTraversalTest, PostOrderOnlyRoot) {
    PostOrderIterator<char> *it = new PostOrderIterator<char>(tree_only_root);
    int i = 0;

    for (it->first(); !it->is_done(); it->next(), i++) {
        ASSERT_EQ('A', it->current_item());
    }
    ASSERT_EQ(1, i);

    delete it;
}

TEST_F(TreeTraversalTest, InOrder) {
    InOrderIterator<char> *it = new InOrderIterator<char>(tree);
    char expected[9] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
    int i = 0;

    for (it->first(); !it->is_done(); it->next(), i++) {
        ASSERT_EQ(expected[i], it->current_item());
    }
    ASSERT_EQ(9, i);

    delete it;
}

TEST_F(TreeTraversalTest, InOrderOnlyRoot) {
    InOrderIterator<char> *it = new InOrderIterator<char>(tree_only_root);
    int i = 0;

    for (it->first(); !it->is_done(); it->next(), i++) {
        ASSERT_EQ('A', it->current_item());
    }
    ASSERT_EQ(1, i);

    delete it;
}

TEST_F(TreeTraversalTest, EulerTour) {
    testing::internal::CaptureStdout();

    euler_tour(tree);

    ASSERT_STREQ("FBAAABDCCCDEEEDBFGGIHHHIIGF", testing::internal::GetCapturedStdout().c_str());
}

TEST_F(TreeTraversalTest, EulerTourOnlyRoot) {
    testing::internal::CaptureStdout();

    euler_tour(tree_only_root);

    ASSERT_STREQ("AAA", testing::internal::GetCapturedStdout().c_str());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
