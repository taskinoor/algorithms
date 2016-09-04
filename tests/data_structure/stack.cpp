#include <array>
#include <gtest/gtest.h>
#include "stack.h"

namespace algtest {

TEST(Stack, Empty) {
    alg::Stack<int> s(2);

    ASSERT_THROW(s.pop(), alg::StackEmptyError);
}

TEST(Stack, Full) {
    alg::Stack<int> s(2);

    ASSERT_NO_THROW(s.push(2));
    ASSERT_NO_THROW(s.push(3));
    ASSERT_THROW(s.push(5), alg::StackFullError);
}

TEST(Stack, PushPop) {
    const int n = 10;
    std::array<int, n> data = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    alg::Stack<int> s(n);

    for (int i = 0; i < n; i++) {
        s.push(data[i]);
    }

    for (int i = 0; i < n; i++) {
        ASSERT_EQ(data[n - 1 - i], s.pop());
    }
}

TEST(Stack, Top) {
    alg::Stack<int> s(2);

    ASSERT_THROW(s.top(), alg::StackEmptyError);

    s.push(2);

    ASSERT_EQ(2, s.top());
    ASSERT_EQ(2, s.top());
}

TEST(Stack, Count) {
    int n = 17;
    int d1 = 13;
    int d2 = 7;
    alg::Stack<int> s(n);

    ASSERT_EQ(0, s.count());

    for (int i = 0; i < n; i++) {
        s.push(i);
    }

    ASSERT_EQ(n, s.count());

    for (int i = 0; i < d1; i++) {
        s.pop();
    }

    ASSERT_EQ(n - d1, s.count());

    for (int i = 0; i < d2; i++) {
        s.push(i);
    }

    ASSERT_EQ(n - d1 + d2, s.count());

    for (int i = 0; i < n - d1 + d2; i++) {
        s.pop();
    }

    ASSERT_EQ(0, s.count());
}

}
