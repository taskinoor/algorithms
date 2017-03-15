#include "alg/sorting/quick_sort/quick_sort.h"
#include "sorting.h"

namespace algtest {

TEST_F(Sorting, QuickSortEmptyArray) {
    ASSERT_NO_THROW(alg::quick_sort(empty.data(), empty.size()));
}

TEST_F(Sorting, QuickSortSingleElement) {
    alg::quick_sort(single_element.data(), single_element.size());

    ASSERT_EQ(expected_single_element, single_element);
}

TEST_F(Sorting, QuickSortAlreadySorted) {
    alg::quick_sort(already_sorted.data(), already_sorted.size());

    ASSERT_EQ(expected, already_sorted);
}

TEST_F(Sorting, QuickSortReverseSorted) {
    alg::quick_sort(reverse_sorted.data(), reverse_sorted.size());

    ASSERT_EQ(expected, reverse_sorted);
}

TEST_F(Sorting, QuickSortRandomOrdered) {
    alg::quick_sort(random_ordered.data(), random_ordered.size());

    ASSERT_EQ(expected, random_ordered);
}

TEST_F(Sorting, QuickSortLargeData) {
    generate_random_large_data();

    alg::quick_sort(large_data.data(), large_data.size());

    assert_large_data_sorted();
}

}
