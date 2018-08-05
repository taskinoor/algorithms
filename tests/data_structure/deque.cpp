#include <type_traits>

#include <gtest/gtest.h>

#include "alg/common/exception.h"
#include "alg/data_structure/deque.h"

namespace algtest {

class Deque : public ::testing::Test {
protected:
    template <class T>
    void assert_empty(alg::ds::Deque<T>& deq) {
        ASSERT_EQ(0, deq.count());

        ASSERT_THROW(deq.back(), alg::except::BufferEmpty);
        ASSERT_THROW(deq.front(), alg::except::BufferEmpty);
        ASSERT_THROW(deq.pop_back(), alg::except::BufferEmpty);
        ASSERT_THROW(deq.pop_front(), alg::except::BufferEmpty);
    }
};

TEST_F(Deque, Operations) {
    alg::ds::Deque<int> deq;

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
        ASSERT_EQ(i, deq.front());

        deq.pop_front();

        ASSERT_EQ(20 - (i + 1), deq.count());
        ASSERT_EQ(i + 1, deq.front());
        ASSERT_EQ(19, deq.back());
    }

    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(19 - i, deq.back());

        deq.pop_back();

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

TEST_F(Deque, BackReference) {
    alg::ds::Deque<int> deq;

    deq.push_back(2);

    deq.back() += 11;

    ASSERT_EQ(13, deq.back());
}

TEST_F(Deque, FrontReference) {
    alg::ds::Deque<int> deq;

    deq.push_front(2);

    deq.front() += 11;

    ASSERT_EQ(13, deq.front());
}

TEST_F(Deque, ConstOverloads) {
    alg::ds::Deque<int> deq;
    const alg::ds::Deque<int> cdeq;

    static_assert(std::is_same<decltype(deq.back()), int&>::value, "");
    static_assert(std::is_same<decltype(cdeq.back()), const int&>::value, "");

    static_assert(std::is_same<decltype(deq.front()), int&>::value, "");
    static_assert(std::is_same<decltype(cdeq.front()), const int&>::value, "");
}

}
