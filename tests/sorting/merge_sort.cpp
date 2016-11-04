#include "alg/sorting/merge_sort/merge_sort.h"
#include "sorting.h"

namespace algtest {

TEST_F(Sorting, MergeSortEmptyArray) {
    ASSERT_NO_THROW(alg::merge_sort(empty.data(), empty.size()));
}

TEST_F(Sorting, MergeSortSingleElement) {
    alg::merge_sort(single_element.data(), single_element.size());

    ASSERT_EQ(expected_single_element, single_element);
}

TEST_F(Sorting, MergeSortAlreadySorted) {
    alg::merge_sort(already_sorted.data(), already_sorted.size());

    ASSERT_EQ(expected, already_sorted);
}

TEST_F(Sorting, MergeSortReverseSorted) {
    alg::merge_sort(reverse_sorted.data(), reverse_sorted.size());

    ASSERT_EQ(expected, reverse_sorted);
}

TEST_F(Sorting, MergeSortRandomOrdered) {
    alg::merge_sort(random_ordered.data(), random_ordered.size());

    ASSERT_EQ(expected, random_ordered);
}

}
