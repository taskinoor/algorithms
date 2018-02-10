#include <gtest/gtest.h>

#include "alg/sorting/selection_sort.h"
#include "sorting.h"

namespace algtest {

TEST_F(Sorting, SelectionSortEmptyArray) {
    ASSERT_NO_THROW(alg::sorting::selection_sort(empty.begin(), empty.end()));
}

TEST_F(Sorting, SelectionSortSingleElement) {
    alg::sorting::selection_sort(single_element.begin(), single_element.end());

    ASSERT_EQ(expected_single_element, single_element);
}

TEST_F(Sorting, SelectionSortAlreadySorted) {
    alg::sorting::selection_sort(already_sorted.begin(), already_sorted.end());

    ASSERT_EQ(expected, already_sorted);
}

TEST_F(Sorting, SelectionSortReverseSorted) {
    alg::sorting::selection_sort(reverse_sorted.begin(), reverse_sorted.end());

    ASSERT_EQ(expected, reverse_sorted);
}

TEST_F(Sorting, SelectionSortRandomOrdered) {
    alg::sorting::selection_sort(random_ordered.begin(), random_ordered.end());

    ASSERT_EQ(expected, random_ordered);
}

}
