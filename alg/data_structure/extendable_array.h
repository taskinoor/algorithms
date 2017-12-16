#ifndef ALG_EXTENDABLE_ARRAY_H_
#define ALG_EXTENDABLE_ARRAY_H_

#include <cstddef>

#include <initializer_list>
#include <memory>
#include <stdexcept>

namespace alg {

template <class T, class A = std::allocator<T>>
class ExtendableArray {
public:
    ExtendableArray() = default;
    explicit ExtendableArray(std::size_t capacity);
    ExtendableArray(std::initializer_list<T> lst);

    ExtendableArray(const ExtendableArray<T,A>& rhs);
    ExtendableArray(ExtendableArray<T,A>&& rhs) noexcept;

    ~ExtendableArray();

    std::size_t count() const;
    std::size_t capacity() const;
    T* data_ptr() const;

    void reserve(std::size_t new_capacity);

    void add(int index, const T& element);
    void append(const T& element);
    T remove(int index);

    T& operator[](int index) const;

    ExtendableArray<T,A>& operator=(const ExtendableArray<T,A>& rhs);
    ExtendableArray<T,A>& operator=(ExtendableArray<T,A>&& rhs) noexcept;

private:
    A alloc;

    T* buffer{nullptr};
    std::size_t capacity_{0};
    std::size_t count_{0};

    void clear_memory(std::size_t start, std::size_t end, bool dealloc);
};

template <class T, class A>
ExtendableArray<T,A>::ExtendableArray(std::size_t capacity) {
    reserve(capacity);
}

template <class T, class A>
ExtendableArray<T,A>::ExtendableArray(std::initializer_list<T> lst) {
    reserve(lst.size());

    for (const T& value : lst) {
        alloc.construct(&buffer[count_++], value);
    }
}

template <class T, class A>
ExtendableArray<T,A>::ExtendableArray(const ExtendableArray<T,A>& rhs) {
    reserve(rhs.count_);

    for ( ; count_ < rhs.count_; count_++) {
        alloc.construct(&buffer[count_], rhs.buffer[count_]);
    }
}

template <class T, class A>
ExtendableArray<T,A>::ExtendableArray(ExtendableArray<T,A>&& rhs) noexcept {
    capacity_ = rhs.capacity_;
    count_ = rhs.count_;
    buffer = rhs.buffer;

    rhs.buffer = nullptr;
    rhs.capacity_ = 0;
    rhs.count_ = 0;
}

template <class T, class A>
ExtendableArray<T,A>::~ExtendableArray() {
    clear_memory(0, count_, true);
}

template <class T, class A>
void ExtendableArray<T,A>::clear_memory(std::size_t start, std::size_t end,
        bool dealloc) {

    for (std::size_t i = start; i < end; i++) {
        alloc.destroy(&buffer[i]);
    }

    if (dealloc && buffer) {
        alloc.deallocate(buffer, capacity_);
    }
}

template <class T, class A>
void ExtendableArray<T,A>::reserve(std::size_t new_capacity) {
    if (new_capacity <= capacity_) {
        return;
    }

    T *tmp_buffer = alloc.allocate(new_capacity);

    for (std::size_t i = 0; i < count_; i++) {
        alloc.construct(&tmp_buffer[i], buffer[i]);
    }

    clear_memory(0, count_, true);

    buffer = tmp_buffer;
    capacity_ = new_capacity;
}

template <class T, class A>
std::size_t ExtendableArray<T,A>::count() const {
    return count_;
}

template <class T, class A>
std::size_t ExtendableArray<T,A>::capacity() const {
    return capacity_;
}

template<class T, class A>
T* ExtendableArray<T,A>::data_ptr() const {
    return buffer;
}

template <class T, class A>
void ExtendableArray<T,A>::add(int index, const T& element) {
    if (index < 0 || index > count_) {
        throw std::out_of_range("");
    }

    if (!capacity_) {
        reserve(1);
    } else if (capacity_ == count_) {
        reserve(capacity_ * 2);
    }

    if (index == count_) {
        alloc.construct(&buffer[count_], element);
    } else {
        alloc.construct(&buffer[count_], buffer[count_ - 1]);

        for (int i = count_ - 2; i >= index; i--) {
            buffer[i + 1] = buffer[i];
        }

        buffer[index] = element;
    }

    count_++;
}

template <class T, class A>
void ExtendableArray<T,A>::append(const T& element) {
    add(count_, element);
}

template <class T, class A>
T ExtendableArray<T,A>::remove(int index) {
    if (index < 0 || index >= count_) {
        throw std::out_of_range("");
    }

    T element = buffer[index];

    for (int i = index + 1; i < count_; i++) {
        buffer[i - 1] = buffer[i];
    }

    alloc.destroy(&buffer[count_ - 1]);

    count_--;

    return element;
}

template <class T, class A>
T& ExtendableArray<T,A>::operator[](int index) const {
    if (index < 0 || index >= count_) {
        throw std::out_of_range("");
    }

    return buffer[index];
}

template <class T, class A>
ExtendableArray<T,A>& ExtendableArray<T,A>::operator=(
        const ExtendableArray<T,A>& rhs) {

    if (this == &rhs) {
        return *this;
    }

    if (rhs.count_ > capacity_) {
        T *tmp_buffer = alloc.allocate(rhs.count_);

        for (std::size_t i = 0; i < rhs.count_; i++) {
            alloc.construct(&tmp_buffer[i], rhs.buffer[i]);
        }

        clear_memory(0, count_, true);

        buffer = tmp_buffer;
        count_ = rhs.count_;
        capacity_ = rhs.count_;
    } else {
        clear_memory(0, count_, false);

        for (std::size_t i = 0; i < rhs.count_; i++) {
            alloc.construct(&buffer[i], rhs.buffer[i]);
        }

        count_ = rhs.count_;
    }

    return *this;
}

template <class T, class A>
ExtendableArray<T,A>& ExtendableArray<T,A>::operator=(
        ExtendableArray<T,A>&& rhs) noexcept {

    clear_memory(0, count_, true);

    buffer = rhs.buffer;
    count_ = rhs.count_;
    capacity_ = rhs.capacity_;

    rhs.buffer = nullptr;
    rhs.count_ = 0;
    rhs.capacity_ = 0;

    return *this;
}

}

#endif
