#include <gtest/gtest.h>

#include "queue.h"

TEST(QueueTest, Empty) {
    Queue<int> q(2);

    ASSERT_THROW(q.dequeue(), QueueEmptyError);
}

TEST(QueueTest, Full) {
    Queue<int> q(2);

    ASSERT_NO_THROW(q.enqueue(2));
    ASSERT_NO_THROW(q.enqueue(3));
    ASSERT_THROW(q.enqueue(5), QueueFullError);
}

TEST(QueueTest, EnqueueDequeue) {
    int a[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    int n = 10;
    Queue<int> q(n - 2);

    for (int i = 0; i < n / 2; i++) {
        q.enqueue(a[i]);
    }
    for (int i = 0; i < n / 5; i++) {
        ASSERT_EQ(a[i], q.dequeue());
    }
    for (int i = n / 2; i < n; i++) {
        q.enqueue(a[i]);
    }

    ASSERT_THROW(q.enqueue(31), QueueFullError);

    for (int i = n / 5; i < n; i++) {
        ASSERT_EQ(a[i], q.dequeue());
    }

    ASSERT_THROW(q.dequeue(), QueueEmptyError);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
