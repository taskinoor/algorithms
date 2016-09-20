#include <array>
#include <gtest/gtest.h>
#include "bst.h"
#include "inorder.h"

namespace algtest {

class BST : public ::testing::Test {
protected:
    alg::BST<int> *bst;

    virtual void SetUp() {
        bst = new alg::BST<int>();
        std::array<int, 10> elements = {12, 5, 9, 18, 15, 2, 19, 17, 13, 2};

        for (const auto& e : elements) {
            bst->insert(e);
        }
    }

    virtual void TearDown() {
        delete bst;
    }
};

TEST_F(BST, Insert) {
    const char *expected = "node: 12, left: 5, right: 18, parent: null\nnode: 5, left: 2, right: 9, parent: 12\nnode: 2, left: null, right: 2, parent: 5\nnode: 2, left: null, right: null, parent: 2\nnode: 9, left: null, right: null, parent: 5\nnode: 18, left: 15, right: 19, parent: 12\nnode: 15, left: 13, right: 17, parent: 18\nnode: 13, left: null, right: null, parent: 15\nnode: 17, left: null, right: null, parent: 15\nnode: 19, left: null, right: null, parent: 18\n";

    ASSERT_STREQ(expected, bst->to_string().c_str());
}

TEST_F(BST, InOrderTraversal) {
    constexpr int n = 10;
    alg::InOrderIterator<int> *it = new alg::InOrderIterator<int>(bst);
    std::array<int, n> expected = {2, 2, 5, 9, 12, 13, 15, 17, 18, 19};
    std::array<int, n> result;

    it->first();

    for (int i = 0; !it->is_done(); it->next(), i++) {
        result[i] = it->current_item();
    }

    ASSERT_EQ(expected, result);

    delete it;
}

TEST_F(BST, Search) {
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
        alg::TreeNode<int> *result = bst->search(data[i][0]);
        alg::TreeNode<int> *left = bst->left(result);
        alg::TreeNode<int> *right = bst->right(result);
        alg::TreeNode<int> *parent = bst->parent(result);

        ASSERT_EQ(data[i][0], result->element());
        ASSERT_EQ(data[i][1], left ? left->element() : 0);
        ASSERT_EQ(data[i][2], right ? right->element() : 0);
        ASSERT_EQ(data[i][3], parent ? parent->element() : 0);
    }
}

TEST_F(BST, SearchMissingKey) {
    ASSERT_EQ(nullptr, bst->search(31));
}

TEST_F(BST, Min) {
    ASSERT_EQ(2, bst->min()->element());
}

TEST_F(BST, Max) {
    ASSERT_EQ(19, bst->max()->element());
}

TEST_F(BST, Successor) {
    constexpr int n = 8;
    std::array<int, n> data = {5, 9, 12, 13, 15, 17, 18, 19};

    ASSERT_EQ(2, bst->successor(bst->search(2))->element());
    ASSERT_EQ(nullptr, bst->successor(bst->search(data[n - 1])));

    for (int i = 0; i < n - 1; i++) {
        ASSERT_EQ(data[i + 1], bst->successor(bst->search(data[i]))->element());
    }
}

TEST_F(BST, Predecessor) {
    constexpr int n = 9;
    std::array<int, n> data = {2, 5, 9, 12, 13, 15, 17, 18, 19};

    for (int i = n - 1; i > 0; i--) {
        ASSERT_EQ(data[i - 1],
                bst->predecessor(bst->search(data[i]))->element());
    }

    ASSERT_EQ(nullptr, bst->predecessor(bst->search(2)));
}

TEST_F(BST, RemoveRoot) {
    const char *expected = "node: 13, left: 5, right: 18, parent: null\nnode: 5, left: 2, right: 9, parent: 13\nnode: 2, left: null, right: 2, parent: 5\nnode: 2, left: null, right: null, parent: 2\nnode: 9, left: null, right: null, parent: 5\nnode: 18, left: 15, right: 19, parent: 13\nnode: 15, left: null, right: 17, parent: 18\nnode: 17, left: null, right: null, parent: 15\nnode: 19, left: null, right: null, parent: 18\n";

    bst->remove(bst->root());

    ASSERT_STREQ(expected, bst->to_string().c_str());
}

TEST_F(BST, RemoveLeaf) {
    const char *expected = "node: 12, left: 5, right: 18, parent: null\nnode: 5, left: 2, right: 9, parent: 12\nnode: 2, left: null, right: 2, parent: 5\nnode: 2, left: null, right: null, parent: 2\nnode: 9, left: null, right: null, parent: 5\nnode: 18, left: 15, right: 19, parent: 12\nnode: 15, left: null, right: 17, parent: 18\nnode: 17, left: null, right: null, parent: 15\nnode: 19, left: null, right: null, parent: 18\n";

    bst->remove(bst->search(13));

    ASSERT_STREQ(expected, bst->to_string().c_str());
}

TEST_F(BST, RemoveNodeWithOneChild) {
    const char *expected = "node: 12, left: 5, right: 18, parent: null\nnode: 5, left: 2, right: 9, parent: 12\nnode: 2, left: null, right: null, parent: 5\nnode: 9, left: null, right: null, parent: 5\nnode: 18, left: 15, right: 19, parent: 12\nnode: 15, left: 13, right: 17, parent: 18\nnode: 13, left: null, right: null, parent: 15\nnode: 17, left: null, right: null, parent: 15\nnode: 19, left: null, right: null, parent: 18\n";

    bst->remove(bst->search(2));

    ASSERT_STREQ(expected, bst->to_string().c_str());
}

TEST_F(BST, RemoveNodeWithSuccessorImmediateRight) {
    const char *expected = "node: 12, left: 5, right: 19, parent: null\nnode: 5, left: 2, right: 9, parent: 12\nnode: 2, left: null, right: 2, parent: 5\nnode: 2, left: null, right: null, parent: 2\nnode: 9, left: null, right: null, parent: 5\nnode: 19, left: 15, right: null, parent: 12\nnode: 15, left: 13, right: 17, parent: 19\nnode: 13, left: null, right: null, parent: 15\nnode: 17, left: null, right: null, parent: 15\n";

    bst->remove(bst->search(18));

    ASSERT_STREQ(expected, bst->to_string().c_str());
}

}
