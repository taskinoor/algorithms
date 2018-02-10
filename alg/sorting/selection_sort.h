#ifndef ALG_SORTING_SELECTION_SORT_H_
#define ALG_SORTING_SELECTION_SORT_H_

#include <algorithm>

namespace alg {
namespace sorting {

template <class ForwardIt>
void selection_sort(ForwardIt first, ForwardIt last) {
    for ( ; first != last; ++first) {
        ForwardIt min_pos = std::min_element(first, last);

        if (min_pos != first) {
            std::iter_swap(min_pos, first);
        }
    }
}

}
}

#endif
