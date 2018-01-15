#ifndef ALG_SEARCHING_LINEAR_SEARCH_H_
#define ALG_SEARCHING_LINEAR_SEARCH_H_

#include <cstddef>

namespace alg {
namespace searching {

template <class T>
int linear_search(T* a, T key, std::size_t n) {
    for (int i = 0; i < n; i++) {
        if (a[i] == key) {
            return i;
        }
    }

    return -1;
}

}
}

#endif
