#include <gtest/gtest.h>

#include "alg/sorting/insertion_sort.h"
#include "sorting.h"

namespace algtest {

TEST_F(Sorting, InsertionSortEmptyArray) {
    ASSERT_NO_THROW(alg::sorting::insertion_sort(empty.begin(), empty.end()));
}

TEST_F(Sorting, InsertionSortSingleElement) {
    alg::sorting::insertion_sort(single_element.begin(), single_element.end());

    ASSERT_EQ(expected_single_element, single_element);
}

TEST_F(Sorting, InsertionSortAlreadySorted) {
    alg::sorting::insertion_sort(already_sorted.begin(), already_sorted.end());

    ASSERT_EQ(expected, already_sorted);
}

TEST_F(Sorting, InsertionSortReverseSorted) {
    alg::sorting::insertion_sort(reverse_sorted.begin(), reverse_sorted.end());

    ASSERT_EQ(expected, reverse_sorted);
}

TEST_F(Sorting, InsertionSortRandomOrdered) {
    alg::sorting::insertion_sort(random_ordered.begin(), random_ordered.end());

    ASSERT_EQ(expected, random_ordered);
}

}
