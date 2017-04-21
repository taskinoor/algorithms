#ifndef ALG_HEAP_SORT_H_
#define ALG_HEAP_SORT_H_

#include "alg/common/utils.h"
#include "alg/data_structure/heap/binary/binary_heap.h"

namespace alg {

template <class T>
void heap_sort(T *a, int n);

}

#include "heap_sort.tpp"

#endif
