#include <gtest/gtest.h>

#include "alg/common/exception.h"
#include "alg/data_structure/deque.h"

namespace algtest {

class Deque : public ::testing::Test {
protected:
    template <class T>
    void assert_empty(alg::Deque<T>& deq) {
        ASSERT_EQ(0, deq.count());

        ASSERT_THROW(deq.back(), alg::except::BufferEmpty);
        ASSERT_THROW(deq.front(), alg::except::BufferEmpty);
        ASSERT_THROW(deq.pop_back(), alg::except::BufferEmpty);
        ASSERT_THROW(deq.pop_front(), alg::except::BufferEmpty);
    }
};

TEST_F(Deque, Operations) {
    alg::Deque<int> deq;

    assert_empty(deq);

    for (int i = 9; i >= 0; --i) {
        deq.push_front(i);

        ASSERT_EQ(9, deq.back());
        ASSERT_EQ(i, deq.front());
        ASSERT_EQ(10 - i, deq.count());
    }

    for (int i = 10; i < 20; ++i) {
        deq.push_back(i);

        ASSERT_EQ(i, deq.back());
        ASSERT_EQ(0, deq.front());
        ASSERT_EQ(i + 1, deq.count());
    }

    for (int i = 0; i < 15; ++i) {
        ASSERT_EQ(i, deq.pop_front());
        ASSERT_EQ(20 - (i + 1), deq.count());
        ASSERT_EQ(i + 1, deq.front());
        ASSERT_EQ(19, deq.back());
    }

    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(19 - i, deq.pop_back());
        ASSERT_EQ(5 - (i + 1), deq.count());

        if (i < 4) {
            ASSERT_EQ(15, deq.front());
            ASSERT_EQ(19 - (i + 1), deq.back());
        } else {
            ASSERT_THROW(deq.front(), alg::except::BufferEmpty);
            ASSERT_THROW(deq.back(), alg::except::BufferEmpty);
        }
    }

    assert_empty(deq);
}

}
