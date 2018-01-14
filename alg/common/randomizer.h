#ifndef ALG_COMMON_RANDOMIZER_H_
#define ALG_COMMON_RANDOMIZER_H_

#include <random>

namespace alg {
namespace randomizer {

std::mt19937& engine();

int uniform_int(int a, int b);
double uniform_double(double a, double b);

}
}

#endif
