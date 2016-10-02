#ifndef ALG_MERGE_SORT_H_
#define ALG_MERGE_SORT_H_

namespace alg {

template <class T>
void merge_sort(T *a, int n);

template <class T>
void merge_sort(T *a, int p, int r);

template <class T>
void merge(T *a, int p, int q, int r);

}

#include "merge_sort.tpp"

#endif
