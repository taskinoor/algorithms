#include <gtest/gtest.h>
#include "josephus.h"

namespace algtest {

TEST(Josephus, SurvivorUsingQueue) {
    ASSERT_EQ(13, alg::josephus_queue(14, 2));
    ASSERT_EQ(4, alg::josephus_queue(7, 3));
    ASSERT_EQ(4, alg::josephus_queue(5, 7));
}

TEST(Josephus, SurvivorUsingOST) {
    ASSERT_EQ(13, alg::josephus_ost(14, 2));
    ASSERT_EQ(4, alg::josephus_ost(7, 3));
    ASSERT_EQ(4, alg::josephus_ost(5, 7));
}

}
