#ifndef ALG_UTILS_H_
#define ALG_UTILS_H_

#include <cstddef>

#include <memory>

namespace alg {
namespace utils {

template <class T>
int min_index(T* a, std::size_t n, int start = 0) {
    int index = start;
    T value = a[index];

    for (int i = start + 1; i < n; i++) {
        if (a[i] < value) {
            index = i;
            value = a[index];
        }
    }

    return index;
}

template <class T, class A>
void clear_buffer(T* buffer, A& alloc, std::size_t begin, std::size_t end,
        std::size_t capacity, bool dealloc) {

    if (!buffer) {
        return;
    }

    for (std::size_t i = begin; i < end; i++) {
        std::allocator_traits<A>::destroy(alloc, buffer + i);
    }

    if (dealloc) {
        std::allocator_traits<A>::deallocate(alloc, buffer, capacity);
    }
}

}
}

#endif
