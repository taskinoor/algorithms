#ifndef ALG_EXCEPT_EXCEPTION_H_
#define ALG_EXCEPT_EXCEPTION_H_

#include <stdexcept>

namespace alg {
namespace except {

class BufferFull : public std::out_of_range {
public:
    BufferFull() : std::out_of_range("Buffer is full") {}
};

class BufferEmpty : public std::out_of_range {
public:
    BufferEmpty() : std::out_of_range("Buffer is empty") {}
};

class ItemNotFound : public std::invalid_argument {
public:
    ItemNotFound() : std::invalid_argument("Item not found") {}
};

}
}

#endif
