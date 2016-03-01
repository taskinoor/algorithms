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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
