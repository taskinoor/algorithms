#ifndef ALG_SORTING_SELECTION_SORT_H_
#define ALG_SORTING_SELECTION_SORT_H_

#include <algorithm>

#include "alg/common/utils.h"

namespace alg {
namespace sorting {

template <class T>
void selection_sort(T* a, int n) {
    for (int i = 0; i < n - 1; ++i) {
        int index = utils::min_index(a, n, i);

        if (index != i) {
            std::swap(a[index], a[i]);
        }
    }
}

}
}

#endif
