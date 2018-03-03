#ifndef ALG_RANDOMIZER_RANDOMIZER_H_
#define ALG_RANDOMIZER_RANDOMIZER_H_

#include <random>

namespace alg {
namespace randomizer {

inline std::mt19937& engine() {
    static std::random_device rd;
    static std::mt19937 e{rd()};

    return e;
}

template <class IntType>
IntType uniform_int(IntType a, IntType b) {
    static std::uniform_int_distribution<IntType> dist;
    using param_t = typename decltype(dist)::param_type;

    return dist(engine(), param_t{a, b});
}

template <class RealType>
RealType uniform_real(RealType a, RealType b) {
    static std::uniform_real_distribution<RealType> dist;
    using param_t = typename decltype(dist)::param_type;

    return dist(engine(), param_t{a, b});
}

}
}

#endif
