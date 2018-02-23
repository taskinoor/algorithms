#ifndef ALG_DS_EXTENDABLE_ARRAY_H_
#define ALG_DS_EXTENDABLE_ARRAY_H_

#include <cstddef>

#include <initializer_list>
#include <memory>
#include <stdexcept>

#include "alg/common/utils.h"

namespace alg {
namespace ds {

template <class T>
class ExtendableArray {
public:
    using allocator_type = std::allocator<T>;

    ExtendableArray() = default;
    explicit ExtendableArray(std::size_t count);
    ExtendableArray(std::initializer_list<T> lst);

    ExtendableArray(const ExtendableArray<T>& rhs);
    ExtendableArray(ExtendableArray<T>&& rhs) noexcept;

    ~ExtendableArray();

    std::size_t count() const;
    std::size_t capacity() const;

    T* data_ptr();
    const T* data_ptr() const;

    void reserve(std::size_t new_capacity);

    void add(std::size_t index, const T& element);
    void append(const T& element);

    T remove(std::size_t index);

    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

    ExtendableArray<T>& operator=(const ExtendableArray<T>& rhs) &;
    ExtendableArray<T>& operator=(ExtendableArray<T>&& rhs) & noexcept;

private:
    allocator_type alloc;

    T* buffer{nullptr};
    std::size_t capacity_{0};
    std::size_t count_{0};
};

template <class T>
ExtendableArray<T>::ExtendableArray(std::size_t count) {
    reserve(count);

    for (count_ = 0; count_ < count; ++count_) {
        std::allocator_traits<allocator_type>::construct(alloc,
                &buffer[count_], T());
    }
}

template <class T>
ExtendableArray<T>::ExtendableArray(std::initializer_list<T> lst) {
    reserve(lst.size());

    for (const T& value : lst) {
        std::allocator_traits<allocator_type>::construct(alloc,
                &buffer[count_++], value);
    }
}

template <class T>
ExtendableArray<T>::ExtendableArray(const ExtendableArray<T>& rhs) {
    reserve(rhs.count_);

    for ( ; count_ < rhs.count_; ++count_) {
        std::allocator_traits<allocator_type>::construct(alloc,
                &buffer[count_], rhs.buffer[count_]);
    }
}

template <class T>
ExtendableArray<T>::ExtendableArray(ExtendableArray<T>&& rhs) noexcept {
    capacity_ = rhs.capacity_;
    count_ = rhs.count_;
    buffer = rhs.buffer;

    rhs.buffer = nullptr;
    rhs.capacity_ = 0;
    rhs.count_ = 0;
}

template <class T>
ExtendableArray<T>::~ExtendableArray() {
    utils::clear_buffer(buffer, alloc, 0, count_, capacity_, true);
}

template <class T>
void ExtendableArray<T>::reserve(std::size_t new_capacity) {
    if (new_capacity <= capacity_) {
        return;
    }

    T* tmp_buffer = std::allocator_traits<allocator_type>::allocate(alloc,
            new_capacity);

    for (std::size_t i = 0; i < count_; ++i) {
        std::allocator_traits<allocator_type>::construct(alloc,
                &tmp_buffer[i], buffer[i]);
    }

    utils::clear_buffer(buffer, alloc, 0, count_, capacity_, true);

    buffer = tmp_buffer;
    capacity_ = new_capacity;
}

template <class T>
std::size_t ExtendableArray<T>::count() const {
    return count_;
}

template <class T>
std::size_t ExtendableArray<T>::capacity() const {
    return capacity_;
}

template <class T>
T* ExtendableArray<T>::data_ptr() {
    return buffer;
}

template <class T>
const T* ExtendableArray<T>::data_ptr() const {
    return buffer;
}

template <class T>
void ExtendableArray<T>::add(std::size_t index, const T& element) {
    if (index > count_) {
        throw std::out_of_range("");
    }

    if (!capacity_) {
        reserve(1);
    } else if (capacity_ == count_) {
        reserve(capacity_ * 2);
    }

    if (index == count_) {
        std::allocator_traits<allocator_type>::construct(alloc,
                &buffer[count_], element);
    } else {
        std::allocator_traits<allocator_type>::construct(alloc,
                &buffer[count_], buffer[count_ - 1]);

        for (int i = count_ - 2; i >= static_cast<int>(index); --i) {
            buffer[i + 1] = buffer[i];
        }

        buffer[index] = element;
    }

    ++count_;
}

template <class T>
void ExtendableArray<T>::append(const T& element) {
    add(count_, element);
}

template <class T>
T ExtendableArray<T>::remove(std::size_t index) {
    if (index >= count_) {
        throw std::out_of_range("");
    }

    T element = buffer[index];

    for (std::size_t i = index + 1; i < count_; ++i) {
        buffer[i - 1] = buffer[i];
    }

    std::allocator_traits<allocator_type>::destroy(alloc, &buffer[count_ - 1]);

    --count_;

    return element;
}

template <class T>
T& ExtendableArray<T>::operator[](std::size_t index) {
    return const_cast<T&>(static_cast<const ExtendableArray<T>&>(*this)[index]);
}

template <class T>
const T& ExtendableArray<T>::operator[](std::size_t index) const {
    if (index >= count_) {
        throw std::out_of_range("");
    }

    return buffer[index];
}

template <class T>
ExtendableArray<T>& ExtendableArray<T>::operator=(
        const ExtendableArray<T>& rhs) & {

    if (this == &rhs) {
        return *this;
    }

    if (rhs.count_ > capacity_) {
        T* tmp_buffer = std::allocator_traits<allocator_type>::allocate(alloc,
                rhs.count_);

        for (std::size_t i = 0; i < rhs.count_; ++i) {
            std::allocator_traits<allocator_type>::construct(alloc,
                    &tmp_buffer[i], rhs.buffer[i]);
        }

        utils::clear_buffer(buffer, alloc, 0, count_, capacity_, true);

        buffer = tmp_buffer;
        count_ = rhs.count_;
        capacity_ = rhs.count_;
    } else {
        utils::clear_buffer(buffer, alloc, 0, count_, capacity_, false);

        for (std::size_t i = 0; i < rhs.count_; ++i) {
            std::allocator_traits<allocator_type>::construct(alloc,
                    &buffer[i], rhs.buffer[i]);
        }

        count_ = rhs.count_;
    }

    return *this;
}

template <class T>
ExtendableArray<T>& ExtendableArray<T>::operator=(
        ExtendableArray<T>&& rhs) & noexcept {

    utils::clear_buffer(buffer, alloc, 0, count_, capacity_, true);

    buffer = rhs.buffer;
    count_ = rhs.count_;
    capacity_ = rhs.capacity_;

    rhs.buffer = nullptr;
    rhs.count_ = 0;
    rhs.capacity_ = 0;

    return *this;
}

}
}

#endif
