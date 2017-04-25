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

}

#include "array.tpp"

#endif
