#ifndef ALG_SORTING_BUBBLE_SORT_H_
#define ALG_SORTING_BUBBLE_SORT_H_

#include <algorithm>

namespace alg {
namespace sorting {

template <class RandomIt>
void bubble_sort(RandomIt first, RandomIt last) {
    for (RandomIt i = first; last - i > 1; ++i) {
        for (RandomIt j = last - 1; j > i; --j) {
            if (*j < *(j - 1)) {
                std::iter_swap(j, j - 1);
            }
        }
    }
}

}
}

#endif
