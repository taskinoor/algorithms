#ifndef ALG_SEARCHING_LINEAR_SEARCH_H_
#define ALG_SEARCHING_LINEAR_SEARCH_H_

namespace alg {
namespace searching {

template <class InputIt, class T>
InputIt linear_search(InputIt first, InputIt last, const T& key) {
    for (InputIt it = first; it != last; ++it) {
        if (*it == key) {
            return it;
        }
    }

    return last;
}

}
}

#endif
