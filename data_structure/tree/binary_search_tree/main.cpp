#include <gtest/gtest.h>

#include "bst.h"
#include "inorder.h"

class BSTTest : public ::testing::Test {
protected:
    BST<int> *bst;

    virtual void SetUp() {
        bst = new BST<int>();
        int elements[] = {12, 5, 9, 18, 15, 2, 19, 17, 13, 2};
        int n = 10;

        for (int i = 0; i < n; i++) {
            bst->insert(elements[i]);
        }
    }

    virtual void TearDown() {
        delete bst;
    }
};

TEST_F(BSTTest, Insert) {
    testing::internal::CaptureStdout();
    const char *expected = "node: 12, left: 5, right: 18, parent: null\nnode: 5, left: 2, right: 9, parent: 12\nnode: 2, left: null, right: 2, parent: 5\nnode: 2, left: null, right: null, parent: 2\nnode: 9, left: null, right: null, parent: 5\nnode: 18, left: 15, right: 19, parent: 12\nnode: 15, left: 13, right: 17, parent: 18\nnode: 13, left: null, right: null, parent: 15\nnode: 17, left: null, right: null, parent: 15\nnode: 19, left: null, right: null, parent: 18\n";

    bst->print();

    ASSERT_STREQ(expected, testing::internal::GetCapturedStdout().c_str());
}

TEST_F(BSTTest, InOrderTraversal) {
    InOrderIterator<int> *it = new InOrderIterator<int>(bst);
    int expected[10] = {2, 2, 5, 9, 12, 13, 15, 17, 18, 19};
    int i = 0;

    for (it->first(); !it->is_done(); it->next(), i++) {
        ASSERT_EQ(expected[i], it->current_item());
    }
    ASSERT_EQ(10, i);

    delete it;
}

TEST_F(BSTTest, Search) {
    int n = 9;
    int data[9][4] = {
        12, 5, 18, 0,
        5, 2, 9, 12,
        18, 15, 19, 12,
        2, 0, 2, 5,
        9, 0, 0, 5,
        15, 13, 17, 18,
        19, 0, 0, 18,
        13, 0, 0, 15,
        17, 0, 0, 15
    };

    for (int i = 0; i < n; i++) {
        Node<int> *result = bst->search(data[i][0]);
        Node<int> *left = bst->left(result);
        Node<int> *right = bst->right(result);
        Node<int> *parent = bst->parent(result);

        ASSERT_EQ(data[i][0], result->get_element());
        ASSERT_EQ(data[i][1], left ? left->get_element() : 0);
        ASSERT_EQ(data[i][2], right ? right->get_element() : 0);
        ASSERT_EQ(data[i][3], parent ? parent->get_element() : 0);
    }
}

TEST_F(BSTTest, SearchMissingKey) {
    ASSERT_EQ(NULL, bst->search(31));
}

TEST_F(BSTTest, Min) {
    ASSERT_EQ(2, bst->min()->get_element());
}

TEST_F(BSTTest, Max) {
    ASSERT_EQ(19, bst->max()->get_element());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
