#ifndef ALG_HEAP_SORT_H_
#define ALG_HEAP_SORT_H_

#include "alg/common/utils.h"
#include "alg/data_structure/heap/binary/binary_heap.h"

namespace alg {

template <class T>
void heap_sort(T *a, int n) {
    heap::binary::build_heap(a, n, heap::binary::HeapType::MAX);

    while (n > 1) {
        swap(a[0], a[n - 1]);
        n--;
        heap::binary::max_heapify(a, 0, n);
    }
}

}

#endif
