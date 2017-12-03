#ifndef ALG_BUBBLE_SORT_H_
#define ALG_BUBBLE_SORT_H_

#include "alg/common/utils.h"

namespace alg {

template <class T>
void bubble_sort(T *a, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = n - 1; j > i; j--) {
            if (a[j] < a[j - 1]) {
                swap(a[j], a[j - 1]);
            }
        }
    }
}

}

#endif
