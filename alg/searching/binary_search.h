#ifndef ALG_SEARCHING_BINARY_SEARCH_H_
#define ALG_SEARCHING_BINARY_SEARCH_H_

namespace alg {
namespace searching {

template <class RandomIt, class T>
RandomIt binary_search(RandomIt first, RandomIt last, const T& key) {
    RandomIt low = first;
    RandomIt high = last;

    while (low < high) {
        RandomIt mid = low + (high - low) / 2;

        if (key < *mid) {
            high = mid;
        } else if (key > *mid) {
            low = mid + 1;
        } else {
            return mid;
        }
    }

    return last;
}

}
}

#endif
