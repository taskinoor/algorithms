#include <gtest/gtest.h>

#include "alg/sorting/insertion_sort.h"
#include "sorting.h"

namespace algtest {

TEST_F(Sorting, InsertionSortEmptyArray) {
    ASSERT_NO_THROW(alg::sorting::insertion_sort(empty.data(), empty.size()));
}

TEST_F(Sorting, InsertionSortSingleElement) {
    alg::sorting::insertion_sort(single_element.data(), single_element.size());

    ASSERT_EQ(expected_single_element, single_element);
}

TEST_F(Sorting, InsertionSortAlreadySorted) {
    alg::sorting::insertion_sort(already_sorted.data(), already_sorted.size());

    ASSERT_EQ(expected, already_sorted);
}

TEST_F(Sorting, InsertionSortReverseSorted) {
    alg::sorting::insertion_sort(reverse_sorted.data(), reverse_sorted.size());

    ASSERT_EQ(expected, reverse_sorted);
}

TEST_F(Sorting, InsertionSortRandomOrdered) {
    alg::sorting::insertion_sort(random_ordered.data(), random_ordered.size());

    ASSERT_EQ(expected, random_ordered);
}

}
