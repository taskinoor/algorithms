#include <gtest/gtest.h>

#include "stack.h"

TEST(StackTest, Empty) {
    Stack<int> s(2);

    ASSERT_THROW(s.pop(), StackEmptyError);
}

TEST(StackTest, Full) {
    Stack<int> s(2);

    ASSERT_NO_THROW(s.push(2));
    ASSERT_NO_THROW(s.push(3));
    ASSERT_THROW(s.push(5), StackFullError);
}

TEST(StackTest, PushPop) {
    int a[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    int n = 10;
    Stack<int> s(n);

    for (int i = 0; i < n; i++) {
        s.push(a[i]);
    }
    for (int i = 0; i < n; i++) {
        ASSERT_EQ(a[n - 1 - i], s.pop());
    }
}

TEST(StackTest, Count) {
    size_t n = 17, d1 = 13, d2 = 7;
    Stack<int> s(n);

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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
