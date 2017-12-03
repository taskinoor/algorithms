#include "alg/sorting/quick_sort.h"
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

TEST_F(Sorting, RandomizedQuickSortEmptyArray) {
    ASSERT_NO_THROW(alg::quick_sort(empty.data(), empty.size(),
            alg::QSPartitionStrategy::RANDOMIZED));
}

TEST_F(Sorting, RandomizedQuickSortSingleElement) {
    alg::quick_sort(single_element.data(), single_element.size(),
            alg::QSPartitionStrategy::RANDOMIZED);

    ASSERT_EQ(expected_single_element, single_element);
}

TEST_F(Sorting, RandomizedQuickSortAlreadySorted) {
    alg::quick_sort(already_sorted.data(), already_sorted.size(),
            alg::QSPartitionStrategy::RANDOMIZED);

    ASSERT_EQ(expected, already_sorted);
}

TEST_F(Sorting, RandomizedQuickSortReverseSorted) {
    alg::quick_sort(reverse_sorted.data(), reverse_sorted.size(),
            alg::QSPartitionStrategy::RANDOMIZED);

    ASSERT_EQ(expected, reverse_sorted);
}

TEST_F(Sorting, RandomizedQuickSortRandomOrdered) {
    alg::quick_sort(random_ordered.data(), random_ordered.size(),
            alg::QSPartitionStrategy::RANDOMIZED);

    ASSERT_EQ(expected, random_ordered);
}

TEST_F(Sorting, RandomizedQuickSortLargeData) {
    generate_random_large_data();

    alg::quick_sort(large_data.data(), large_data.size(),
            alg::QSPartitionStrategy::RANDOMIZED);

    assert_large_data_sorted();
}

TEST_F(Sorting, HoareQuickSortEmptyArray) {
    ASSERT_NO_THROW(alg::quick_sort(empty.data(), empty.size(),
            alg::QSPartitionStrategy::HOARE));
}

TEST_F(Sorting, HoareQuickSortSingleElement) {
    alg::quick_sort(single_element.data(), single_element.size(),
            alg::QSPartitionStrategy::HOARE);

    ASSERT_EQ(expected_single_element, single_element);
}

TEST_F(Sorting, HoareQuickSortAlreadySorted) {
    alg::quick_sort(already_sorted.data(), already_sorted.size(),
            alg::QSPartitionStrategy::HOARE);

    ASSERT_EQ(expected, already_sorted);
}

TEST_F(Sorting, HoareQuickSortReverseSorted) {
    alg::quick_sort(reverse_sorted.data(), reverse_sorted.size(),
            alg::QSPartitionStrategy::HOARE);

    ASSERT_EQ(expected, reverse_sorted);
}

TEST_F(Sorting, HoareQuickSortRandomOrdered) {
    alg::quick_sort(random_ordered.data(), random_ordered.size(),
            alg::QSPartitionStrategy::HOARE);

    ASSERT_EQ(expected, random_ordered);
}

TEST_F(Sorting, HoareQuickSortLargeData) {
    generate_random_large_data();

    alg::quick_sort(large_data.data(), large_data.size(),
            alg::QSPartitionStrategy::HOARE);

    assert_large_data_sorted();
}

}
