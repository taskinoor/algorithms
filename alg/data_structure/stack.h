#ifndef ALG_STACK_H_
#define ALG_STACK_H_

#include <cstddef>

#include <memory>

#include "alg/common/exception.h"

namespace alg {

template <class T, class A = std::allocator<T>>
class Stack {
public:
    explicit Stack(std::size_t n);
    ~Stack();

    void push(const T& element);
    T pop();
    T top();
    std::size_t count();

private:
    A alloc;

    T* buffer{nullptr};
    int top_{-1};
    std::size_t size{0};

    void reserve();
    void clear_memory();
};

template <class T, class A>
Stack<T,A>::Stack(std::size_t n) : size{n} {
}

template <class T, class A>
Stack<T,A>::~Stack() {
    clear_memory();
}

template <class T, class A>
void Stack<T,A>::push(const T& element) {
    if (top_ == size - 1) {
        throw except::BufferFull();
    }

    if (!buffer) {
        reserve();
    }

    top_++;

    std::allocator_traits<A>::construct(alloc, &buffer[top_], element);
}

template <class T, class A>
T Stack<T,A>::pop() {
    if (top_ == -1) {
        throw except::BufferEmpty();
    }

    T element = buffer[top_];

    std::allocator_traits<A>::destroy(alloc, &buffer[top_]);

    top_--;

    return element;
}

template <class T, class A>
T Stack<T,A>::top() {
    if (top_ == -1) {
        throw except::BufferEmpty();
    }

    return buffer[top_];
}

template <class T, class A>
std::size_t Stack<T,A>::count() {
    return top_ + 1;
}

template <class T, class A>
void Stack<T,A>::reserve() {
    buffer = std::allocator_traits<A>::allocate(alloc, size);
}

template <class T, class A>
void Stack<T,A>::clear_memory() {
    for (int i = 0; i <= top_; i++) {
        std::allocator_traits<A>::destroy(alloc, &buffer[i]);
    }

    std::allocator_traits<A>::deallocate(alloc, buffer, size);
}

}

#endif
