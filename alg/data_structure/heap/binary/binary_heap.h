#ifndef ALG_BINARY_HEAP_H_
#define ALG_BINARY_HEAP_H_

#include "alg/common/utils.h"

namespace alg {
namespace heap {
namespace binary {

enum class HeapType {
    MIN,
    MAX
};

int parent(int i);
int left(int i);
int right(int i);

template <class T>
void build_heap(T *a, int n, HeapType type);

template <class T>
void min_heapify(T *a, int i, int n);

template <class T>
void max_heapify(T *a, int i, int n);

template <class T>
void heapify(T *a, int i, int n, HeapType type);

}
}
}

#include "binary_heap.tpp"

#endif
