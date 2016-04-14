#include <gtest/gtest.h>
#include "josephus.h"

TEST(JosephusTest, Survivor) {
    ASSERT_EQ(13, josephus(14, 2));
    ASSERT_EQ(4, josephus(7, 3));
    ASSERT_EQ(4, josephus(5, 7));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
