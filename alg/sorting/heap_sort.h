#ifndef ALG_SORTING_HEAP_SORT_H_
#define ALG_SORTING_HEAP_SORT_H_

#include <algorithm>

#include "alg/data_structure/binary_heap.h"

namespace alg {
namespace sorting {

template <class T>
void heap_sort(T* a, int n) {
    ds::heap::binary::build_heap(a, n, ds::heap::binary::Type::MAX);

    while (n > 1) {
        std::swap(a[0], a[n - 1]);
        --n;
        ds::heap::binary::max_heapify(a, 0, n);
    }
}

}
}

#endif
