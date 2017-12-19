#ifndef ALG_STACK_H_
#define ALG_STACK_H_

#include <cstddef>

#include <memory>

#include "alg/common/exception.h"
#include "alg/common/utils.h"

namespace alg {

template <class T, class A = std::allocator<T>>
class Stack {
public:
    explicit Stack(std::size_t n);

    Stack(const Stack<T,A>& rhs);
    Stack(Stack<T,A>&& rhs) noexcept;

    ~Stack();

    void push(const T& element);
    T pop();
    T top() const;
    std::size_t count() const;

    Stack<T,A>& operator=(const Stack<T,A>& rhs);
    Stack<T,A>& operator=(Stack<T,A>&& rhs) noexcept;

private:
    A alloc;

    T* buffer{nullptr};
    int top_{-1};
    std::size_t size{0};

    void reserve();
};

template <class T, class A>
Stack<T,A>::Stack(std::size_t n) : size{n} {
}

template <class T, class A>
Stack<T,A>::Stack(const Stack<T,A>& rhs) {
    size = rhs.size;

    reserve();

    for (int i = 0; i <= rhs.top_; i++) {
        std::allocator_traits<A>::construct(alloc, &buffer[i], rhs.buffer[i]);
    }

    top_ = rhs.top_;
}

template <class T, class A>
Stack<T,A>::Stack(Stack<T,A>&& rhs) noexcept {
    buffer = rhs.buffer;
    size = rhs.size;
    top_ = rhs.top_;

    rhs.buffer = nullptr;
    rhs.top_ = -1;
}

template <class T, class A>
Stack<T,A>::~Stack() {
    utils::clear_buffer(buffer, alloc, 0, top_ + 1, size, true);
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
T Stack<T,A>::top() const {
    if (top_ == -1) {
        throw except::BufferEmpty();
    }

    return buffer[top_];
}

template <class T, class A>
std::size_t Stack<T,A>::count() const {
    return top_ + 1;
}

template <class T, class A>
Stack<T,A>& Stack<T,A>::operator=(const Stack<T,A>& rhs) {
    if (this == &rhs) {
        return *this;
    }

    if (size == rhs.size) {
        utils::clear_buffer(buffer, alloc, 0, top_ + 1, size, false);
    } else {
        utils::clear_buffer(buffer, alloc, 0, top_ + 1, size, true);

        size = rhs.size;

        reserve();
    }

    for (int i = 0; i <= rhs.top_; i++) {
        std::allocator_traits<A>::construct(alloc, &buffer[i], rhs.buffer[i]);
    }

    top_ = rhs.top_;

    return *this;
}

template <class T, class A>
Stack<T,A>& Stack<T,A>::operator=(Stack<T,A>&& rhs) noexcept {
    utils::clear_buffer(buffer, alloc, 0, top_ + 1, size, true);

    buffer = rhs.buffer;
    size = rhs.size;
    top_ = rhs.top_;

    rhs.buffer = nullptr;
    rhs.top_ = -1;

    return *this;
}

template <class T, class A>
void Stack<T,A>::reserve() {
    buffer = std::allocator_traits<A>::allocate(alloc, size);
}

}

#endif
