#include <gtest/gtest.h>

#include "alg/sorting/merge_sort.h"
#include "sorting.h"

namespace algtest {

TEST_F(Sorting, MergeSortEmptyArray) {
    ASSERT_NO_THROW(alg::sorting::merge_sort(empty.data(), empty.size()));
}

TEST_F(Sorting, MergeSortSingleElement) {
    alg::sorting::merge_sort(single_element.data(), single_element.size());

    ASSERT_EQ(expected_single_element, single_element);
}

TEST_F(Sorting, MergeSortAlreadySorted) {
    alg::sorting::merge_sort(already_sorted.data(), already_sorted.size());

    ASSERT_EQ(expected, already_sorted);
}

TEST_F(Sorting, MergeSortReverseSorted) {
    alg::sorting::merge_sort(reverse_sorted.data(), reverse_sorted.size());

    ASSERT_EQ(expected, reverse_sorted);
}

TEST_F(Sorting, MergeSortRandomOrdered) {
    alg::sorting::merge_sort(random_ordered.data(), random_ordered.size());

    ASSERT_EQ(expected, random_ordered);
}

TEST_F(Sorting, MergeSortLargeData) {
    generate_random_large_data();

    alg::sorting::merge_sort(large_data.data(), large_data.size());

    assert_large_data_sorted();
}

}
