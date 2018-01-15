#include <array>
#include <string>

#include <gtest/gtest.h>

#include "alg/data_structure/tree/binary_tree.h"
#include "alg/data_structure/tree/bst.h"
#include "alg/data_structure/tree/traversal/inorder.h"

namespace algtest {

class BST : public ::testing::Test {
protected:
    alg::BST<int>* bst;

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

TEST_F(BST, SentinelNode) {
    ASSERT_EQ(nullptr, bst->nil());
}

TEST_F(BST, Insert) {
    std::string expected = "E: 12, L: 5, R: 18, P: nil\nE: 5, L: 2, R: 9, P: 12\nE: 2, L: nil, R: 2, P: 5\nE: 2, L: nil, R: nil, P: 2\nE: 9, L: nil, R: nil, P: 5\nE: 18, L: 15, R: 19, P: 12\nE: 15, L: 13, R: 17, P: 18\nE: 13, L: nil, R: nil, P: 15\nE: 17, L: nil, R: nil, P: 15\nE: 19, L: nil, R: nil, P: 18\n";

    ASSERT_EQ(expected, bst->to_string());
}

TEST_F(BST, InOrderTraversal) {
    constexpr int n = 10;
    alg::InOrderIterator<int>* it = new alg::InOrderIterator<int>(bst);
    std::array<int, n> expected = {2, 2, 5, 9, 12, 13, 15, 17, 18, 19};
    std::array<int, n> result;

    it->first();

    for (int i = 0; !it->is_done(); it->next(), ++i) {
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

    for (int i = 0; i < n; ++i) {
        alg::TreeNode<int>* result = bst->search(data[i][0]);
        alg::TreeNode<int>* left = bst->left(result);
        alg::TreeNode<int>* right = bst->right(result);
        alg::TreeNode<int>* parent = bst->parent(result);

        ASSERT_EQ(data[i][0], result->element());
        ASSERT_EQ(data[i][1], left ? left->element() : 0);
        ASSERT_EQ(data[i][2], right ? right->element() : 0);
        ASSERT_EQ(data[i][3], parent ? parent->element() : 0);
    }
}

TEST_F(BST, SearchMissingKey) {
    ASSERT_EQ(bst->nil(), bst->search(31));
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
    ASSERT_EQ(bst->nil(), bst->successor(bst->search(data[n - 1])));

    for (int i = 0; i < n - 1; ++i) {
        ASSERT_EQ(data[i + 1], bst->successor(bst->search(data[i]))->element());
    }
}

TEST_F(BST, Predecessor) {
    constexpr int n = 9;
    std::array<int, n> data = {2, 5, 9, 12, 13, 15, 17, 18, 19};

    for (int i = n - 1; i > 0; --i) {
        ASSERT_EQ(data[i - 1],
                bst->predecessor(bst->search(data[i]))->element());
    }

    ASSERT_EQ(bst->nil(), bst->predecessor(bst->search(2)));
}

TEST_F(BST, RemoveRoot) {
    std::string expected = "E: 13, L: 5, R: 18, P: nil\nE: 5, L: 2, R: 9, P: 13\nE: 2, L: nil, R: 2, P: 5\nE: 2, L: nil, R: nil, P: 2\nE: 9, L: nil, R: nil, P: 5\nE: 18, L: 15, R: 19, P: 13\nE: 15, L: nil, R: 17, P: 18\nE: 17, L: nil, R: nil, P: 15\nE: 19, L: nil, R: nil, P: 18\n";

    bst->remove(bst->root());

    ASSERT_EQ(expected, bst->to_string());
}

TEST_F(BST, RemoveLeaf) {
    std::string expected = "E: 12, L: 5, R: 18, P: nil\nE: 5, L: 2, R: 9, P: 12\nE: 2, L: nil, R: 2, P: 5\nE: 2, L: nil, R: nil, P: 2\nE: 9, L: nil, R: nil, P: 5\nE: 18, L: 15, R: 19, P: 12\nE: 15, L: nil, R: 17, P: 18\nE: 17, L: nil, R: nil, P: 15\nE: 19, L: nil, R: nil, P: 18\n";

    bst->remove(bst->search(13));

    ASSERT_EQ(expected, bst->to_string());
}

TEST_F(BST, RemoveNodeWithOneChild) {
    std::string expected = "E: 12, L: 5, R: 18, P: nil\nE: 5, L: 2, R: 9, P: 12\nE: 2, L: nil, R: nil, P: 5\nE: 9, L: nil, R: nil, P: 5\nE: 18, L: 15, R: 19, P: 12\nE: 15, L: 13, R: 17, P: 18\nE: 13, L: nil, R: nil, P: 15\nE: 17, L: nil, R: nil, P: 15\nE: 19, L: nil, R: nil, P: 18\n";

    bst->remove(bst->search(2));

    ASSERT_EQ(expected, bst->to_string());
}

TEST_F(BST, RemoveNodeWithSuccessorImmediateRight) {
    std::string expected = "E: 12, L: 5, R: 19, P: nil\nE: 5, L: 2, R: 9, P: 12\nE: 2, L: nil, R: 2, P: 5\nE: 2, L: nil, R: nil, P: 2\nE: 9, L: nil, R: nil, P: 5\nE: 19, L: 15, R: nil, P: 12\nE: 15, L: 13, R: 17, P: 19\nE: 13, L: nil, R: nil, P: 15\nE: 17, L: nil, R: nil, P: 15\n";

    bst->remove(bst->search(18));

    ASSERT_EQ(expected, bst->to_string());
}

}
