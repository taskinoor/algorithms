#include <gtest/gtest.h>

#include "alg/sorting/quick_sort.h"
#include "sorting.h"

namespace algtest {

TEST_F(Sorting, QuickSortEmptyArray) {
    ASSERT_NO_THROW(alg::sorting::quick_sort(empty.data(), empty.size()));
}

TEST_F(Sorting, QuickSortSingleElement) {
    alg::sorting::quick_sort(single_element.data(), single_element.size());

    ASSERT_EQ(expected_single_element, single_element);
}

TEST_F(Sorting, QuickSortAlreadySorted) {
    alg::sorting::quick_sort(already_sorted.data(), already_sorted.size());

    ASSERT_EQ(expected, already_sorted);
}

TEST_F(Sorting, QuickSortReverseSorted) {
    alg::sorting::quick_sort(reverse_sorted.data(), reverse_sorted.size());

    ASSERT_EQ(expected, reverse_sorted);
}

TEST_F(Sorting, QuickSortRandomOrdered) {
    alg::sorting::quick_sort(random_ordered.data(), random_ordered.size());

    ASSERT_EQ(expected, random_ordered);
}

TEST_F(Sorting, QuickSortLargeData) {
    generate_random_large_data();

    alg::sorting::quick_sort(large_data.data(), large_data.size());

    assert_large_data_sorted();
}

TEST_F(Sorting, RandomizedQuickSortEmptyArray) {
    ASSERT_NO_THROW(alg::sorting::quick_sort(empty.data(), empty.size(),
            alg::sorting::PartitionStrategy::RANDOMIZED));
}

TEST_F(Sorting, RandomizedQuickSortSingleElement) {
    alg::sorting::quick_sort(single_element.data(), single_element.size(),
            alg::sorting::PartitionStrategy::RANDOMIZED);

    ASSERT_EQ(expected_single_element, single_element);
}

TEST_F(Sorting, RandomizedQuickSortAlreadySorted) {
    alg::sorting::quick_sort(already_sorted.data(), already_sorted.size(),
            alg::sorting::PartitionStrategy::RANDOMIZED);

    ASSERT_EQ(expected, already_sorted);
}

TEST_F(Sorting, RandomizedQuickSortReverseSorted) {
    alg::sorting::quick_sort(reverse_sorted.data(), reverse_sorted.size(),
            alg::sorting::PartitionStrategy::RANDOMIZED);

    ASSERT_EQ(expected, reverse_sorted);
}

TEST_F(Sorting, RandomizedQuickSortRandomOrdered) {
    alg::sorting::quick_sort(random_ordered.data(), random_ordered.size(),
            alg::sorting::PartitionStrategy::RANDOMIZED);

    ASSERT_EQ(expected, random_ordered);
}

TEST_F(Sorting, RandomizedQuickSortLargeData) {
    generate_random_large_data();

    alg::sorting::quick_sort(large_data.data(), large_data.size(),
            alg::sorting::PartitionStrategy::RANDOMIZED);

    assert_large_data_sorted();
}

TEST_F(Sorting, HoareQuickSortEmptyArray) {
    ASSERT_NO_THROW(alg::sorting::quick_sort(empty.data(), empty.size(),
            alg::sorting::PartitionStrategy::HOARE));
}

TEST_F(Sorting, HoareQuickSortSingleElement) {
    alg::sorting::quick_sort(single_element.data(), single_element.size(),
            alg::sorting::PartitionStrategy::HOARE);

    ASSERT_EQ(expected_single_element, single_element);
}

TEST_F(Sorting, HoareQuickSortAlreadySorted) {
    alg::sorting::quick_sort(already_sorted.data(), already_sorted.size(),
            alg::sorting::PartitionStrategy::HOARE);

    ASSERT_EQ(expected, already_sorted);
}

TEST_F(Sorting, HoareQuickSortReverseSorted) {
    alg::sorting::quick_sort(reverse_sorted.data(), reverse_sorted.size(),
            alg::sorting::PartitionStrategy::HOARE);

    ASSERT_EQ(expected, reverse_sorted);
}

TEST_F(Sorting, HoareQuickSortRandomOrdered) {
    alg::sorting::quick_sort(random_ordered.data(), random_ordered.size(),
            alg::sorting::PartitionStrategy::HOARE);

    ASSERT_EQ(expected, random_ordered);
}

TEST_F(Sorting, HoareQuickSortLargeData) {
    generate_random_large_data();

    alg::sorting::quick_sort(large_data.data(), large_data.size(),
            alg::sorting::PartitionStrategy::HOARE);

    assert_large_data_sorted();
}

}
