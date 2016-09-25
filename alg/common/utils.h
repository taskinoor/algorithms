#ifndef ALG_UTILS_H_
#define ALG_UTILS_H_

#include <cstddef>

namespace alg {

template <class T>
T max(const T& a, const T& b);

template <class T>
int min_index(T *a, std::size_t n, int start = 0);

template <class T>
void swap(T& a, T& b);

}

#include "utils.tpp"

#endif
