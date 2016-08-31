#include <gtest/gtest.h>

#include "deque.h"

TEST(DequeTest, Operations) {
    Deque<int> d;

    ASSERT_EQ(0, d.count());
    ASSERT_THROW(d.back(), DequeEmptyError);
    ASSERT_THROW(d.front(), DequeEmptyError);
    ASSERT_THROW(d.pop_back(), DequeEmptyError);
    ASSERT_THROW(d.pop_front(), DequeEmptyError);

    for (int i = 9; i >= 0; i--) {
        d.push_front(i);

        ASSERT_EQ(9, d.back());
        ASSERT_EQ(i, d.front());
        ASSERT_EQ(10 - i, d.count());
    }

    for (int i = 10; i < 20; i++) {
        d.push_back(i);

        ASSERT_EQ(i, d.back());
        ASSERT_EQ(0, d.front());
        ASSERT_EQ(i + 1, d.count());
    }

    for (int i = 0; i < 15; i++) {
        ASSERT_EQ(i, d.pop_front());
        ASSERT_EQ(20 - (i + 1), d.count());
        ASSERT_EQ(i + 1, d.front());
        ASSERT_EQ(19, d.back());
    }
    for (int i = 0; i < 5; i++) {
        ASSERT_EQ(19 - i, d.pop_back());
        ASSERT_EQ(5 - (i + 1), d.count());

        if (i < 4) {
            ASSERT_EQ(15, d.front());
            ASSERT_EQ(19 - (i + 1), d.back());
        } else {
            ASSERT_THROW(d.front(), DequeEmptyError);
            ASSERT_THROW(d.back(), DequeEmptyError);
        }
    }

    ASSERT_EQ(0, d.count());
    ASSERT_THROW(d.back(), DequeEmptyError);
    ASSERT_THROW(d.front(), DequeEmptyError);
    ASSERT_THROW(d.pop_back(), DequeEmptyError);
    ASSERT_THROW(d.pop_front(), DequeEmptyError);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
