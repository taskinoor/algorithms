#ifndef ALG_EXTENDABLE_ARRAY_H_
#define ALG_EXTENDABLE_ARRAY_H_

#include <cstddef>

#include <algorithm>
#include <initializer_list>
#include <stdexcept>

namespace alg {

class InvalidIndexError : public std::runtime_error {
public:
    InvalidIndexError() : std::runtime_error("Invalid index") {}
};

template <class T>
class ExtendableArray {
private:
    T *buffer;
    std::size_t capacity;
    int n;

    void grow();

public:
    ExtendableArray(std::size_t capacity = 1);
    ExtendableArray(std::initializer_list<T> lst);

    ExtendableArray(const ExtendableArray<T>& that);
    ExtendableArray(ExtendableArray<T>&& that) noexcept;

    virtual ~ExtendableArray();

    std::size_t count() const;
    T *data_ptr() const;

    void add(int index, const T& element);
    void append(const T& element);
    T remove(int index);

    T& operator[](int index) const;
};

template <class T>
ExtendableArray<T>::ExtendableArray(std::size_t capacity) {
    this->capacity = capacity;
    buffer = new T[capacity];
    n = 0;
}

template <class T>
ExtendableArray<T>::ExtendableArray(std::initializer_list<T> lst) {
    capacity = lst.size();
    buffer = new T[capacity];
    n = capacity;

    std::copy(lst.begin(), lst.end(), buffer);
}

template <class T>
ExtendableArray<T>::ExtendableArray(const ExtendableArray<T>& that) {
    capacity = that.capacity;
    buffer = new T[capacity];
    n = that.n;

    std::copy(&that.buffer[0], &that.buffer[n], buffer);
}

template <class T>
ExtendableArray<T>::ExtendableArray(ExtendableArray<T>&& that) noexcept {
    capacity = that.capacity;
    n = that.n;
    buffer = that.buffer;

    that.buffer = nullptr;
}

template <class T>
ExtendableArray<T>::~ExtendableArray() {
    delete[] buffer;
}

template <class T>
void ExtendableArray<T>::grow() {
    capacity *= 2;
    T *tmp_buffer = new T[capacity];

    for (int i = 0; i < n; i++) {
        tmp_buffer[i] = buffer[i];
    }

    delete[] buffer;
    buffer = tmp_buffer;
}

template <class T>
std::size_t ExtendableArray<T>::count() const {
    return n;
}

template<class T>
T *ExtendableArray<T>::data_ptr() const {
    return buffer;
}

template <class T>
void ExtendableArray<T>::add(int index, const T& element) {
    if (index < 0 || index > n) {
        throw InvalidIndexError();
    }

    if (n == capacity) {
        grow();
    }

    for (int i = n - 1; i >= index; i--) {
        buffer[i + 1] = buffer[i];
    }

    buffer[index] = element;
    n++;
}

template <class T>
void ExtendableArray<T>::append(const T& element) {
    add(n, element);
}

template <class T>
T ExtendableArray<T>::remove(int index) {
    if (index < 0 || index > n - 1) {
        throw InvalidIndexError();
    }

    T element = buffer[index];

    for (int i = index + 1; i < n; i++) {
        buffer[i - 1] = buffer[i];
    }

    n--;

    return element;
}

template <class T>
T& ExtendableArray<T>::operator[](int index) const {
    if (index < 0 || index >= n) {
        throw InvalidIndexError();
    }

    return buffer[index];
}

}

#endif
