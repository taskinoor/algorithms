#include <cmath>

#include <algorithm>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

#include "alg/common/randomizer.h"
#include "alg/data_structure/tree/binary_tree.h"
#include "alg/data_structure/tree/red_black_tree.h"
#include "alg/data_structure/tree/traversal/inorder.h"
#include "alg/data_structure/tree/traversal/postorder.h"
#include "alg/data_structure/tree/traversal/preorder.h"

namespace algtest {

class RedBlackTree : public ::testing::Test {
protected:
    static alg::ds::tree::RedBlackTree<int>* tree;
    static std::vector<std::pair<bool, int>> keys;
    static int count;

    static void SetUpTestCase() {
        tree = new alg::ds::tree::RedBlackTree<int>();

        constexpr int total = 1000000;
        constexpr int delete_frequency = 5;
        count = total - (total / delete_frequency - 1);

        for (int i = 0; i < total; ++i) {
            keys.push_back(std::make_pair(true, i));
        }

        std::shuffle(keys.begin(), keys.end(), alg::randomizer::engine());
        tree->insert(keys[0].second);

        for (int i = 1; i < total; ++i) {
            tree->insert(keys[i].second);

            if (!(i % delete_frequency)) {
                int j = alg::randomizer::uniform_int(0, i);

                while (!keys[j].first) {
                    j = alg::randomizer::uniform_int(0, i);
                }

                tree->remove(tree->search(keys[j].second));
                keys[j].first = false;
            }
        }
    }

    static void TearDownTestCase() {
        delete tree;
    }
};

alg::ds::tree::RedBlackTree<int>* RedBlackTree::tree = nullptr;
std::vector<std::pair<bool, int>> RedBlackTree::keys = {};

int RedBlackTree::count = 0;

TEST_F(RedBlackTree, Count) {
    ASSERT_NE(0, count);
    ASSERT_EQ(count, tree->count_descendants(tree->root()));
}

TEST_F(RedBlackTree, Height) {
    ASSERT_LE(tree->height(), 2 * std::log2(count + 1));
}

TEST_F(RedBlackTree, RootColor) {
    alg::ds::tree::RBNode<int>* root = (alg::ds::tree::RBNode<int>*)tree->root();

    ASSERT_EQ(alg::ds::tree::RBColor::BLACK, root->color());
}

TEST_F(RedBlackTree, LeafColor) {
    alg::ds::tree::RBNode<int>* nil = (alg::ds::tree::RBNode<int>*)tree->nil();

    ASSERT_EQ(alg::ds::tree::RBColor::BLACK, nil->color());
}

TEST_F(RedBlackTree, ChildOfRed) {
    alg::ds::tree::traversal::PreOrderIterator<int>* iter =
            new alg::ds::tree::traversal::PreOrderIterator<int>(tree);

    int found = 0;

    for (iter->first(); !iter->is_done(); iter->next(), ++found) {
        alg::ds::tree::RBNode<int>* node =
                (alg::ds::tree::RBNode<int>*)iter->current_node();

        alg::ds::tree::RBNode<int>* left =
                (alg::ds::tree::RBNode<int>*)tree->left(node);

        alg::ds::tree::RBNode<int>* right =
                (alg::ds::tree::RBNode<int>*)tree->right(node);

        if (node->color() == alg::ds::tree::RBColor::RED) {
            ASSERT_EQ(alg::ds::tree::RBColor::BLACK, left->color());
            ASSERT_EQ(alg::ds::tree::RBColor::BLACK, right->color());
        }
    }

    ASSERT_EQ(count, found);

    delete iter;
}

TEST_F(RedBlackTree, BlackHeight) {
    alg::ds::tree::traversal::PostOrderIterator<int>* iter =
            new alg::ds::tree::traversal::PostOrderIterator<int>(tree);

    int found = 0;
    int black_height = -1;

    for (iter->first(); !iter->is_done(); iter->next(), ++found) {
        alg::ds::tree::RBNode<int>* node =
                (alg::ds::tree::RBNode<int>*)iter->current_node();

        alg::ds::tree::RBNode<int>* left =
                (alg::ds::tree::RBNode<int>*)tree->left(node);

        alg::ds::tree::RBNode<int>* right =
                (alg::ds::tree::RBNode<int>*)tree->right(node);

        if (left == tree->nil() && right == tree->nil()) {
            int count = 0;

            while (node != tree->nil()) {
                if (node->color() == alg::ds::tree::RBColor::BLACK) {
                    ++count;
                }

                node = (alg::ds::tree::RBNode<int>*)tree->parent(node);
            }

            if (black_height == -1) {
                black_height = count;
            } else {
                ASSERT_EQ(black_height, count);
            }
        }
    }

    ASSERT_EQ(count, found);

    delete iter;
}

TEST_F(RedBlackTree, Search) {
    for (const auto& key : keys) {
        if (key.first) {
            ASSERT_EQ(key.second, tree->search(key.second)->element());
        } else {
            ASSERT_EQ(tree->nil(), tree->search(key.second));
        }
    }
}

TEST_F(RedBlackTree, Sorting) {
    std::vector<int> present_keys = {};

    for (const auto& key : keys) {
        if (key.first) {
            present_keys.push_back(key.second);
        }
    }

    ASSERT_EQ(count, present_keys.size());
    std::sort(present_keys.begin(), present_keys.end());

    alg::ds::tree::traversal::InOrderIterator<int>* iter =
            new alg::ds::tree::traversal::InOrderIterator<int>(tree);

    int i = 0;

    for (iter->first(); !iter->is_done(); iter->next(), ++i) {
        ASSERT_EQ(present_keys[i], iter->current_item());
    }

    ASSERT_EQ(count, i);

    ASSERT_EQ(present_keys[0], tree->min()->element());
    ASSERT_EQ(present_keys[count - 1], tree->max()->element());

    delete iter;
}

TEST_F(RedBlackTree, Rotation) {
    constexpr int n = 6;
    int keys[n] = {7, 11, 9, 18, 14, 19};

    alg::ds::tree::Node<int>* nodes[n];
    alg::ds::tree::RedBlackTree<int>* rb_tree =
            new alg::ds::tree::RedBlackTree<int>();

    alg::ds::tree::Node<int>* nil = rb_tree->nil();

    for (int i = 0; i < n; ++i) {
        nodes[i] = new alg::ds::tree::Node<int>(keys[i], nil, nil, nil);
    }

    alg::ds::tree::Node<int>* begin[n][3] = {
            nil, nil, nodes[1],
            nodes[0], nodes[2], nodes[3],
            nodes[1], nil, nil,
            nodes[1], nodes[4], nodes[5],
            nodes[3], nil, nil,
            nodes[3], nil, nil
    };

    alg::ds::tree::Node<int>* after[n][3] = {
            nil, nil, nodes[3],
            nodes[3], nodes[2], nodes[4],
            nodes[1], nil, nil,
            nodes[0], nodes[1], nodes[5],
            nodes[1], nil, nil,
            nodes[3], nil, nil
    };

    for (int i = 0; i < n; ++i) {
        rb_tree->set_left(nodes[i], begin[i][1]);
        rb_tree->set_right(nodes[i], begin[i][2]);
    }

    rb_tree->rotate(nodes[1], true);

    for (int i = 0; i < n; ++i) {
        ASSERT_EQ(keys[i], nodes[i]->element());
        ASSERT_EQ(after[i][0], rb_tree->parent(nodes[i]));
        ASSERT_EQ(after[i][1], rb_tree->left(nodes[i]));
        ASSERT_EQ(after[i][2], rb_tree->right(nodes[i]));
    }

    rb_tree->rotate(nodes[3], false);

    for (int i = 0; i < n; ++i) {
        ASSERT_EQ(keys[i], nodes[i]->element());
        ASSERT_EQ(begin[i][0], rb_tree->parent(nodes[i]));
        ASSERT_EQ(begin[i][1], rb_tree->left(nodes[i]));
        ASSERT_EQ(begin[i][2], rb_tree->right(nodes[i]));
    }

    for (int i = 0; i < n; ++i) {
        delete nodes[i];
    }

    delete rb_tree;
}

}
