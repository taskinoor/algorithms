#ifndef ALG_MERGE_SORT_H_
#define ALG_MERGE_SORT_H_

#include <cstddef>

namespace alg {

template <class T>
void merge_sort(T *a, std::size_t n);

template <class T>
void merge_sort(T *a, int p, int r);

template <class T>
void merge(T *a, int p, int q, int r);

}

#include "merge_sort.tpp"

#endif
