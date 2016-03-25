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

TEST(LinkedListTest, EmptyList) {
    LinkedList<int> list;

    ASSERT_EQ(NULL, list.first());
    ASSERT_EQ(NULL, list.last());
}

TEST(LinkedListTest, EmptyInsertFirst) {
    LinkedList<int> list;

    list.insert_first(2);

    ASSERT_EQ(2, list.first()->get_element());
    ASSERT_EQ(2, list.last()->get_element());
}

TEST(LinkedListTest, EmptyInsertLast) {
    LinkedList<int> list;

    list.insert_last(2);

    ASSERT_EQ(2, list.first()->get_element());
    ASSERT_EQ(2, list.last()->get_element());
}

TEST(LinkedListTest, InsertAfter) {
    LinkedList<int> list;

    list.insert_first(2);
    list.insert_after(list.first(), 3);
    list.insert_after(list.last(), 5);

    ASSERT_EQ(2, list.first()->get_element());
    ASSERT_EQ(3, list.after(list.first())->get_element());
    ASSERT_EQ(5, list.last()->get_element());
}

TEST(LinkedListTest, InsertBefore) {
    LinkedList<int> list;

    list.insert_last(2);
    list.insert_before(list.last(), 3);
    list.insert_before(list.first(), 5);

    ASSERT_EQ(2, list.last()->get_element());
    ASSERT_EQ(3, list.before(list.last())->get_element());
    ASSERT_EQ(5, list.first()->get_element());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
