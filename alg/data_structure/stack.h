#ifndef ALG_STACK_H_
#define ALG_STACK_H_

#include <cstddef>

#include <memory>

#include "alg/common/exception.h"
#include "alg/common/utils.h"

namespace alg {

template <class T>
class Stack {
public:
    using allocator_type = std::allocator<T>;

    explicit Stack(std::size_t n);

    Stack(const Stack<T>& rhs);
    Stack(Stack<T>&& rhs) noexcept;

    ~Stack();

    void push(const T& element);

    T pop();
    T top() const;

    std::size_t count() const;

    Stack<T>& operator=(const Stack<T>& rhs);
    Stack<T>& operator=(Stack<T>&& rhs) noexcept;

private:
    allocator_type alloc;

    T* buffer{nullptr};

    std::size_t size{0};
    int top_{-1};

    void reserve();
};

template <class T>
Stack<T>::Stack(std::size_t n) : size{n} {
}

template <class T>
Stack<T>::Stack(const Stack<T>& rhs) : size{rhs.size} {
    reserve();

    for (int i = 0; i <= rhs.top_; i++) {
        std::allocator_traits<allocator_type>::construct(alloc,
                &buffer[i], rhs.buffer[i]);
    }

    top_ = rhs.top_;
}

template <class T>
Stack<T>::Stack(Stack<T>&& rhs) noexcept : buffer{rhs.buffer}, size{rhs.size},
        top_{rhs.top_} {

    rhs.buffer = nullptr;
    rhs.top_ = -1;
}

template <class T>
Stack<T>::~Stack() {
    utils::clear_buffer(buffer, alloc, 0, top_ + 1, size, true);
}

template <class T>
void Stack<T>::push(const T& element) {
    if (top_ == size - 1) {
        throw except::BufferFull();
    }

    if (!buffer) {
        reserve();
    }

    top_++;

    std::allocator_traits<allocator_type>::construct(alloc,
            &buffer[top_], element);
}

template <class T>
T Stack<T>::pop() {
    if (top_ == -1) {
        throw except::BufferEmpty();
    }

    T element = buffer[top_];

    std::allocator_traits<allocator_type>::destroy(alloc, &buffer[top_]);

    top_--;

    return element;
}

template <class T>
T Stack<T>::top() const {
    if (top_ == -1) {
        throw except::BufferEmpty();
    }

    return buffer[top_];
}

template <class T>
std::size_t Stack<T>::count() const {
    return top_ + 1;
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& rhs) {
    if (this == &rhs) {
        return *this;
    }

    utils::clear_buffer(buffer, alloc, 0, top_ + 1, size, size != rhs.size);

    if (size != rhs.size) {
        size = rhs.size;

        reserve();
    }

    for (int i = 0; i <= rhs.top_; i++) {
        std::allocator_traits<allocator_type>::construct(alloc,
                &buffer[i], rhs.buffer[i]);
    }

    top_ = rhs.top_;

    return *this;
}

template <class T>
Stack<T>& Stack<T>::operator=(Stack<T>&& rhs) noexcept {
    utils::clear_buffer(buffer, alloc, 0, top_ + 1, size, true);

    buffer = rhs.buffer;
    size = rhs.size;
    top_ = rhs.top_;

    rhs.buffer = nullptr;
    rhs.top_ = -1;

    return *this;
}

template <class T>
void Stack<T>::reserve() {
    buffer = std::allocator_traits<allocator_type>::allocate(alloc, size);
}

}

#endif
