#include <gtest/gtest.h>
#include "josephus.h"

TEST(JosephusTest, SurvivorUsingQueue) {
    ASSERT_EQ(13, josephus_queue(14, 2));
    ASSERT_EQ(4, josephus_queue(7, 3));
    ASSERT_EQ(4, josephus_queue(5, 7));
}

TEST(JosephusTest, SurvivorUsingOST) {
    ASSERT_EQ(13, josephus_ost(14, 2));
    ASSERT_EQ(4, josephus_ost(7, 3));
    ASSERT_EQ(4, josephus_ost(5, 7));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
