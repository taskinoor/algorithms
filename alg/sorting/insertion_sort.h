#ifndef ALG_SORTING_INSERTION_SORT_H_
#define ALG_SORTING_INSERTION_SORT_H_

namespace alg {
namespace sorting {

template <class RandomIt>
void insertion_sort(RandomIt first, RandomIt last) {
    for (RandomIt j = first + 1; j < last; ++j) {
        auto key = *j;
        RandomIt i = j - 1;

        while (i >= first && *i > key) {
            *(i + 1) = *i;
            --i;
        }

        *(i + 1) = key;
    }
}

}
}

#endif
