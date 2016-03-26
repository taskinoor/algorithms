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

TEST(ListIteratorTest, InsertFirst) {
    LinkedList<int> list;
    int a[] = {2, 3, 5, 7, 11, 13, 17};
    int i;

    for (i = 0; i < 7; i++) {
        list.insert_first(a[i]);
    }

    ForwardListIterator<int> *iter_forward = (ForwardListIterator<int> *)list.create_iterator();
    BackwordListIterator<int> *iter_backword = (BackwordListIterator<int> *)list.create_iterator(false);

    for (i = 6, iter_forward->first(); !iter_forward->is_done(); iter_forward->next(), i--) {
        ASSERT_EQ(a[i], iter_forward->current_item());
    }
    for (i = 0, iter_backword->first(); !iter_backword->is_done(); iter_backword->next(), i++) {
        ASSERT_EQ(a[i], iter_backword->current_item());
    }

    list.destroy_iterator(iter_forward);
    list.destroy_iterator(iter_backword);
}

TEST(ListIteratorTest, InsertLast) {
    LinkedList<int> list;
    int a[] = {2, 3, 5, 7, 11, 13, 17};
    int i;

    for (i = 0; i < 7; i++) {
        list.insert_last(a[i]);
    }

    ForwardListIterator<int> *iter_forward = (ForwardListIterator<int> *)list.create_iterator();
    BackwordListIterator<int> *iter_backword = (BackwordListIterator<int> *)list.create_iterator(false);

    for (i = 0, iter_forward->first(); !iter_forward->is_done(); iter_forward->next(), i++) {
        ASSERT_EQ(a[i], iter_forward->current_item());
    }
    for (i = 6, iter_backword->first(); !iter_backword->is_done(); iter_backword->next(), i--) {
        ASSERT_EQ(a[i], iter_backword->current_item());
    }

    list.destroy_iterator(iter_forward);
    list.destroy_iterator(iter_backword);
}

TEST(ListIteratorTest, EmptyList) {
    LinkedList<int> list;

    ForwardListIterator<int> *iter_forward = (ForwardListIterator<int> *)list.create_iterator();
    BackwordListIterator<int> *iter_backword = (BackwordListIterator<int> *)list.create_iterator(false);

    for (iter_forward->first(); !iter_forward->is_done(); iter_forward->next()) {
        FAIL();
    }
    for (iter_backword->first(); !iter_backword->is_done(); iter_backword->next()) {
        FAIL();
    }

    list.destroy_iterator(iter_forward);
    list.destroy_iterator(iter_backword);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
