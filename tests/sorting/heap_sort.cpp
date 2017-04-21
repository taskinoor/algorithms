#include "alg/sorting/heap_sort/heap_sort.h"
#include "sorting.h"

namespace algtest {

TEST_F(Sorting, HeapSortEmptyArray) {
    ASSERT_NO_THROW(alg::heap_sort(empty.data(), empty.size()));
}

TEST_F(Sorting, HeapSortSingleElement) {
    alg::heap_sort(single_element.data(), single_element.size());

    ASSERT_EQ(expected_single_element, single_element);
}

TEST_F(Sorting, HeapSortAlreadySorted) {
    alg::heap_sort(already_sorted.data(), already_sorted.size());

    ASSERT_EQ(expected, already_sorted);
}

TEST_F(Sorting, HeapSortReverseSorted) {
    alg::heap_sort(reverse_sorted.data(), reverse_sorted.size());

    ASSERT_EQ(expected, reverse_sorted);
}

TEST_F(Sorting, HeapSortRandomOrdered) {
    alg::heap_sort(random_ordered.data(), random_ordered.size());

    ASSERT_EQ(expected, random_ordered);
}

TEST_F(Sorting, HeapSortLargeData) {
    generate_random_large_data();

    alg::heap_sort(large_data.data(), large_data.size());

    assert_large_data_sorted();
}

}
