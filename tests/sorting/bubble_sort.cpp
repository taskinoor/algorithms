#include <gtest/gtest.h>

#include "alg/sorting/bubble_sort.h"
#include "sorting.h"

namespace algtest {

TEST_F(Sorting, BubbleSortEmptyArray) {
    ASSERT_NO_THROW(alg::sorting::bubble_sort(empty.begin(), empty.end()));
}

TEST_F(Sorting, BubbleSortSingleElement) {
    alg::sorting::bubble_sort(single_element.begin(), single_element.end());

    ASSERT_EQ(expected_single_element, single_element);
}

TEST_F(Sorting, BubbleSortAlreadySorted) {
    alg::sorting::bubble_sort(already_sorted.begin(), already_sorted.end());

    ASSERT_EQ(expected, already_sorted);
}

TEST_F(Sorting, BubbleSortReverseSorted) {
    alg::sorting::bubble_sort(reverse_sorted.begin(), reverse_sorted.end());

    ASSERT_EQ(expected, reverse_sorted);
}

TEST_F(Sorting, BubbleSortRandomOrdered) {
    alg::sorting::bubble_sort(random_ordered.begin(), random_ordered.end());

    ASSERT_EQ(expected, random_ordered);
}

}
