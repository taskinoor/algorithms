#include "randomizer.h"

namespace alg {
namespace randomizer {

std::mt19937& engine() {
    static std::random_device rd;
    static std::mt19937 e{rd()};

    return e;
}

int uniform_int(int a, int b) {
    static std::uniform_int_distribution<> d;
    using param_t = decltype(d)::param_type;

    return d(engine(), param_t{a, b});
}

double uniform_double(double a, double b) {
    static std::uniform_real_distribution<> d;
    using param_t = decltype(d)::param_type;

    return d(engine(), param_t{a, b});
}

}
}
