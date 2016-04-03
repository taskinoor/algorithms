#include <gtest/gtest.h>

#include "binary_tree.h"

TEST(NodeTest, DefaultElement) {
    Node<int> n;

    ASSERT_EQ(0, n.get_element());
}

TEST(NodeTest, GetElement) {
    Node<int> n(2);

    ASSERT_EQ(2, n.get_element());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
