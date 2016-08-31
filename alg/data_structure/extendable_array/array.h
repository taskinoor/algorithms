#ifndef ARRAY_H_
#define ARRAY_H_

#include <stddef.h>

#include <stdexcept>

class InvalidIndexError : public std::runtime_error {
public:
    InvalidIndexError() : std::runtime_error("Invalid index") {}
};

template <class T>
class ExtendableArray {
private:
    T *buffer;
    size_t capacity;
    int n;

    void grow();
public:
    ExtendableArray(size_t capacity = 1);
    ~ExtendableArray();

    size_t count();

    void add(int, T);
    T remove(int);

    void set(int, T);
    T get(int);
};

#include "array.tpp"

#endif
