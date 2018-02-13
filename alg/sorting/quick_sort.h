#ifndef ALG_SORTING_QUICK_SORT_H_
#define ALG_SORTING_QUICK_SORT_H_

#include <algorithm>

#include "alg/common/randomizer.h"

namespace alg {
namespace sorting {

enum class PartitionStrategy {
    LOMUTO,
    RANDOMIZED,
    HOARE
};

template <class T>
int partition_lomuto(T* a, int p, int r) {
    int i = p - 1;

    for (int j = p; j < r; ++j) {
        if (a[j] <= a[r]) {
            std::swap(a[++i], a[j]);
        }
    }

    std::swap(a[++i], a[r]);

    return i;
}

template <class T>
int partition_randomized(T* a, int p, int r) {
    int i = randomizer::uniform_int(p, r);
    std::swap(a[i], a[r]);

    return partition_lomuto(a, p, r);
}

template <class T>
int partition_hoare(T* a, int p, int r) {
    T x = a[p];
    int i = p - 1;
    int j = r + 1;

    while (true) {
        do {
            --j;
        } while (a[j] > x);

        do {
            ++i;
        } while (a[i] < x);

        if (i >= j) {
            return j;
        }

        std::swap(a[i], a[j]);
    }
}

template <class T>
int partition(T* a, int p, int r, PartitionStrategy st) {
    switch (st) {
    case PartitionStrategy::LOMUTO:
        return partition_lomuto(a, p, r);

    case PartitionStrategy::RANDOMIZED:
        return partition_randomized(a, p, r);

    case PartitionStrategy::HOARE:
        return partition_hoare(a, p, r);

    default:
        return -1;
    }
}

template <class T>
void quick_sort(T* a, int p, int r, PartitionStrategy st) {
    if (p >= r) {
        return;
    }

    int q = partition(a, p, r, st);

    quick_sort(a, p, st == PartitionStrategy::HOARE ? q : q - 1, st);
    quick_sort(a, q + 1, r, st);
}

template <class T>
void quick_sort(T* a, int n, PartitionStrategy st = PartitionStrategy::LOMUTO) {
    quick_sort(a, 0, n - 1, st);
}

}
}

#endif
