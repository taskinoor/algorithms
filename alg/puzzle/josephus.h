#ifndef ALG_PUZZLE_JOSEPHUS_H_
#define ALG_PUZZLE_JOSEPHUS_H_

#include <cstddef>

namespace alg {
namespace puzzle {

std::size_t josephus_queue(std::size_t n, std::size_t k);
std::size_t josephus_ost(std::size_t n, std::size_t k);

}
}

#endif
