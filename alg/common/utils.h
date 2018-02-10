#ifndef ALG_COMMON_UTILS_H_
#define ALG_COMMON_UTILS_H_

#include <cstddef>

#include <memory>

namespace alg {
namespace utils {

template <class T, class A>
void clear_buffer(T* buffer, A& alloc, std::size_t first, std::size_t last,
        std::size_t capacity, bool dealloc) {

    if (!buffer) {
        return;
    }

    for (std::size_t i = first; i < last; ++i) {
        std::allocator_traits<A>::destroy(alloc, buffer + i);
    }

    if (dealloc) {
        std::allocator_traits<A>::deallocate(alloc, buffer, capacity);
    }
}

}
}

#endif
