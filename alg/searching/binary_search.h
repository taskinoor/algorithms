#ifndef ALG_BINARY_SEARCH_H_
#define ALG_BINARY_SEARCH_H_

#include <cstddef>

namespace alg {

template <class T>
int binary_search(T* a, T key, std::size_t n) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (key < a[mid]) {
            high = mid - 1;
        } else if (key > a[mid]) {
            low = mid + 1;
        } else {
            return mid;
        }
    }

    return -1;
}

}

#endif
