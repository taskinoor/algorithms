#ifndef ALG_QUICK_SORT_H_
#define ALG_QUICK_SORT_H_

#include "alg/common/utils.h"

namespace alg {

template <class T>
void quick_sort(T *a, int n);

template <class T>
void quick_sort(T *a, int p, int r);

template <class T>
int qs_partition(T *a, int p, int r);

}

#include "quick_sort.tpp"

#endif
