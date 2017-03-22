#ifndef ALG_QUICK_SORT_H_
#define ALG_QUICK_SORT_H_

#include "alg/common/utils.h"

namespace alg {

enum QSPartitionStrategy {
    LOMUTO
};

template <class T>
void quick_sort(T *a, int n, QSPartitionStrategy st = LOMUTO);

template <class T>
void quick_sort(T *a, int p, int r, QSPartitionStrategy st);

template <class T>
int qs_partition_lomuto(T *a, int p, int r);

}

#include "quick_sort.tpp"

#endif
