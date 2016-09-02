#ifndef ALG_ARRAY_H_
#define ALG_ARRAY_H_

#include <cstddef>
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
    virtual ~ExtendableArray();

    std::size_t count();

    void add(int index, T element);
    T remove(int index);

    void set(int index, T element);
    T get(int index);
};

}

#include "array.tpp"

#endif
