#include <array>
#include <gtest/gtest.h>

#include "alg/data_structure/linked_list.h"

namespace algtest {

TEST(ListNode, DefaultElement) {
    alg::ListNode<int> node;

    ASSERT_EQ(0, node.element());
}

TEST(ListNode, Element) {
    alg::ListNode<int> node(2);

    ASSERT_EQ(2, node.element());
}

TEST(LinkedList, EmptyList) {
    alg::LinkedList<int> list;

    ASSERT_EQ(nullptr, list.first());
    ASSERT_EQ(nullptr, list.last());
}

TEST(LinkedList, EmptyInsertFirst) {
    alg::LinkedList<int> list;

    list.insert_first(2);

    ASSERT_EQ(2, list.first()->element());
    ASSERT_EQ(2, list.last()->element());
}

TEST(LinkedList, EmptyInsertLast) {
    alg::LinkedList<int> list;

    list.insert_last(2);

    ASSERT_EQ(2, list.first()->element());
    ASSERT_EQ(2, list.last()->element());
}

TEST(LinkedList, InsertAfter) {
    alg::LinkedList<int> list;

    list.insert_first(2);
    list.insert_after(list.first(), 3);
    list.insert_after(list.last(), 5);

    ASSERT_EQ(2, list.first()->element());
    ASSERT_EQ(3, list.after(list.first())->element());
    ASSERT_EQ(5, list.last()->element());
}

TEST(LinkedList, InsertBefore) {
    alg::LinkedList<int> list;

    list.insert_last(2);
    list.insert_before(list.last(), 3);
    list.insert_before(list.first(), 5);

    ASSERT_EQ(2, list.last()->element());
    ASSERT_EQ(3, list.before(list.last())->element());
    ASSERT_EQ(5, list.first()->element());
}

TEST(LinkedList, Search) {
    alg::LinkedList<int> list;

    ASSERT_EQ(nullptr, list.search(2));

    list.insert_last(2);
    list.insert_last(3);
    list.insert_last(5);

    ASSERT_EQ(nullptr, list.search(7));

    ASSERT_EQ(2, list.search(2)->element());
    ASSERT_EQ(nullptr, list.before(list.search(2)));
    ASSERT_EQ(list.search(3), list.after(list.search(2)));

    ASSERT_EQ(3, list.search(3)->element());
    ASSERT_EQ(list.search(2), list.before(list.search(3)));
    ASSERT_EQ(list.search(5), list.after(list.search(3)));

    ASSERT_EQ(5, list.search(5)->element());
    ASSERT_EQ(list.search(3), list.before(list.search(5)));
    ASSERT_EQ(nullptr, list.after(list.search(5)));
}

TEST(LinkedList, Remove) {
    alg::LinkedList<int> list;
    std::array<int, 7> data = {2, 3, 5, 7, 11, 13, 17};

    for (const auto& i : data) {
        list.insert_first(i);
    }

    list.remove(list.search(2));
    list.remove(list.search(17));
    list.remove(list.search(7));

    std::array<int, 4> expected = {3, 5, 11, 13};

    alg::ForwardListIterator<int> *iter_forward =
            (alg::ForwardListIterator<int> *)list.create_iterator();
    alg::BackwardListIterator<int> *iter_backward =
            (alg::BackwardListIterator<int> *)list.create_iterator(false);

    for (int i = 3; !iter_forward->is_done(); iter_forward->next(), i--) {
        ASSERT_EQ(expected[i], iter_forward->current_item());
    }
    for (int i = 0; !iter_backward->is_done(); iter_backward->next(), i++) {
        ASSERT_EQ(expected[i], iter_backward->current_item());
    }

    list.destroy_iterator(iter_forward);
    list.destroy_iterator(iter_backward);
}

TEST(ListIterator, InsertFirst) {
    alg::LinkedList<int> list;
    std::array<int, 7> data = {2, 3, 5, 7, 11, 13, 17};

    for (const auto& i : data) {
        list.insert_first(i);
    }

    alg::ForwardListIterator<int> *iter_forward =
            (alg::ForwardListIterator<int> *)list.create_iterator();
    alg::BackwardListIterator<int> *iter_backward =
            (alg::BackwardListIterator<int> *)list.create_iterator(false);

    for (int i = 6; !iter_forward->is_done(); iter_forward->next(), i--) {
        ASSERT_EQ(data[i], iter_forward->current_item());
    }
    for (int i = 0; !iter_backward->is_done(); iter_backward->next(), i++) {
        ASSERT_EQ(data[i], iter_backward->current_item());
    }

    list.destroy_iterator(iter_forward);
    list.destroy_iterator(iter_backward);
}

TEST(ListIterator, InsertLast) {
    alg::LinkedList<int> list;
    std::array<int, 7> data = {2, 3, 5, 7, 11, 13, 17};

    for (const auto& i : data) {
        list.insert_last(i);
    }

    alg::ForwardListIterator<int> *iter_forward =
            (alg::ForwardListIterator<int> *)list.create_iterator();
    alg::BackwardListIterator<int> *iter_backward =
            (alg::BackwardListIterator<int> *)list.create_iterator(false);

    for (int i = 0; !iter_forward->is_done(); iter_forward->next(), i++) {
        ASSERT_EQ(data[i], iter_forward->current_item());
    }
    for (int i = 6; !iter_backward->is_done(); iter_backward->next(), i--) {
        ASSERT_EQ(data[i], iter_backward->current_item());
    }

    list.destroy_iterator(iter_forward);
    list.destroy_iterator(iter_backward);
}

TEST(ListIterator, EmptyList) {
    alg::LinkedList<int> list;

    alg::ForwardListIterator<int> *iter_forward =
            (alg::ForwardListIterator<int> *)list.create_iterator();
    alg::BackwardListIterator<int> *iter_backward =
            (alg::BackwardListIterator<int> *)list.create_iterator(false);

    for (; !iter_forward->is_done(); iter_forward->next()) {
        FAIL();
    }
    for (; !iter_backward->is_done(); iter_backward->next()) {
        FAIL();
    }

    list.destroy_iterator(iter_forward);
    list.destroy_iterator(iter_backward);
}

}
