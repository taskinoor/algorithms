#include <gtest/gtest.h>

#include "list.h"

TEST(NodeTest, DefaultElement) {
    Node<int> node;

    ASSERT_EQ(0, node.get_element());
}

TEST(NodeTest, Element) {
    Node<int> node(2);

    ASSERT_EQ(2, node.get_element());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
