#include <gtest/gtest.h>

#include "array.h"

TEST(ExtendableArrayTest, InvalidIndex) {
    ExtendableArray<int> array;

    ASSERT_THROW(array.get(-1), InvalidIndexError);
    ASSERT_THROW(array.get(0), InvalidIndexError);

    ASSERT_THROW(array.add(-1, 2), InvalidIndexError);
    ASSERT_THROW(array.add(1, 2), InvalidIndexError);

    ASSERT_THROW(array.set(-1, 2), InvalidIndexError);
    ASSERT_THROW(array.set(0, 2), InvalidIndexError);

    ASSERT_THROW(array.remove(-1), InvalidIndexError);
    ASSERT_THROW(array.remove(0), InvalidIndexError);
}

TEST(ExtendableArrayTest, Operations) {
    ExtendableArray<int> array;

    array.add(0, 2);
    array.add(1, 3);
    array.add(2, 5);
    array.add(2, 7);
    array.add(0, 11);
    array.add(5, 13);
    array.add(1, 17);

    ASSERT_EQ(7, array.count());

    int expected[] = {11, 17, 2, 3, 7, 5, 13};

    for (int i = 0; i < 7; i++) {
        ASSERT_EQ(expected[i], array.get(i));
    }

    array.set(0, 19);
    array.set(6, 23);
    array.set(3, 29);

    expected[0] = 19;
    expected[6] = 23;
    expected[3] = 29;

    for (int i = 0; i < 7; i++) {
        ASSERT_EQ(expected[i], array.get(i));
    }

    ASSERT_EQ(19, array.remove(0));
    ASSERT_EQ(7, array.remove(3));
    ASSERT_EQ(23, array.remove(4));

    ASSERT_EQ(4, array.count());

    int expected_after_remove[] = {17, 2, 29, 5};

    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(expected_after_remove[i], array.get(i));
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
