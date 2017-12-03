#ifndef ALG_SELECTION_SORT_H_
#define ALG_SELECTION_SORT_H_

#include "alg/common/utils.h"

namespace alg {

template <class T>
void selection_sort(T *a, int n) {
    for (int i = 0; i < n - 1; i++) {
        int index = utils::min_index(a, n, i);

        if (index != i) {
            utils::swap(a[index], a[i]);
        }
    }
}

}

#endif
