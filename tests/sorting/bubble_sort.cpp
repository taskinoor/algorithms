#include <gtest/gtest.h>

#include "alg/sorting/bubble_sort.h"
#include "sorting.h"

namespace algtest {

TEST_F(Sorting, BubbleSortEmptyArray) {
    ASSERT_NO_THROW(alg::bubble_sort(empty.data(), empty.size()));
}

TEST_F(Sorting, BubbleSortSingleElement) {
    alg::bubble_sort(single_element.data(), single_element.size());

    ASSERT_EQ(expected_single_element, single_element);
}

TEST_F(Sorting, BubbleSortAlreadySorted) {
    alg::bubble_sort(already_sorted.data(), already_sorted.size());

    ASSERT_EQ(expected, already_sorted);
}

TEST_F(Sorting, BubbleSortReverseSorted) {
    alg::bubble_sort(reverse_sorted.data(), reverse_sorted.size());

    ASSERT_EQ(expected, reverse_sorted);
}

TEST_F(Sorting, BubbleSortRandomOrdered) {
    alg::bubble_sort(random_ordered.data(), random_ordered.size());

    ASSERT_EQ(expected, random_ordered);
}

}
