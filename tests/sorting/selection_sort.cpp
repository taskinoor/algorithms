#include <gtest/gtest.h>

#include "alg/sorting/selection_sort.h"
#include "sorting.h"

namespace algtest {

TEST_F(Sorting, SelectionSortEmptyArray) {
    ASSERT_NO_THROW(alg::sorting::selection_sort(empty.data(), empty.size()));
}

TEST_F(Sorting, SelectionSortSingleElement) {
    alg::sorting::selection_sort(single_element.data(), single_element.size());

    ASSERT_EQ(expected_single_element, single_element);
}

TEST_F(Sorting, SelectionSortAlreadySorted) {
    alg::sorting::selection_sort(already_sorted.data(), already_sorted.size());

    ASSERT_EQ(expected, already_sorted);
}

TEST_F(Sorting, SelectionSortReverseSorted) {
    alg::sorting::selection_sort(reverse_sorted.data(), reverse_sorted.size());

    ASSERT_EQ(expected, reverse_sorted);
}

TEST_F(Sorting, SelectionSortRandomOrdered) {
    alg::sorting::selection_sort(random_ordered.data(), random_ordered.size());

    ASSERT_EQ(expected, random_ordered);
}

}
