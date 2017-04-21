#include "binary_heap.h"

namespace alg {
namespace heap {
namespace binary {

int parent(int i) {
    return i ? (i - 1) / 2 : -1;
}

int left(int i) {
    return 2 * i + 1;
}

int right(int i) {
    return 2 * (i + 1);
}

}
}
}
