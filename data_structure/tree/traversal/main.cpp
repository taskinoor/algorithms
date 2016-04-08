#include <gtest/gtest.h>

#include "preorder.h"

class TreeIteratorTest : public ::testing::Test {
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
            for (int j = 0; j < 2; j++) {
                if (child_map[i][j] != -1) {
                    tree->set_child(node[i], node[index(child_map[i][j])], j);
                }
            }
        }

        tree_only_root = new BinaryTree<char>(new Node<char>('A'));
    }

    virtual void TearDown() {
        delete tree;
        delete tree_only_root;
    }
};

TEST_F(TreeIteratorTest, PreOrder) {
    PreOrderIterator<char> *it = new PreOrderIterator<char>(tree);
    char expected[9] = {'F', 'B', 'A', 'D', 'C', 'E', 'G', 'I', 'H'};
    int i = 0;

    for (it->first(); !it->is_done(); it->next(), i++) {
        ASSERT_EQ(expected[i], it->current_item());
    }

    delete it;
}

TEST_F(TreeIteratorTest, PreOrderOnlyRoot) {
    PreOrderIterator<char> *it = new PreOrderIterator<char>(tree_only_root);
    int i = 0;

    for (it->first(); !it->is_done(); it->next(), i++) {
        ASSERT_EQ('A', it->current_item());
        if (i > 0) {
            FAIL();
        }
    }

    delete it;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
