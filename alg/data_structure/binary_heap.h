#ifndef ALG_DS_HEAP_BINARY_BINARY_HEAP_H_
#define ALG_DS_HEAP_BINARY_BINARY_HEAP_H_

#include <algorithm>

namespace alg {
namespace ds {
namespace heap {
namespace binary {

enum class Type {
    MIN,
    MAX
};

inline int parent(int i) {
    return i ? (i - 1) / 2 : -1;
}

inline int left(int i) {
    return 2 * i + 1;
}

inline int right(int i) {
    return 2 * (i + 1);
}

template <class T>
void min_heapify(T* a, int i, int n) {
    while (true) {
        int left_ = left(i);
        int right_ = right(i);
        int smallest = i;

        if (left_ < n && a[left_] < a[i]) {
            smallest = left_;
        }
        if (right_ < n && a[right_] < a[smallest]) {
            smallest = right_;
        }

        if (smallest == i) {
            break;
        }

        std::swap(a[i], a[smallest]);
        i = smallest;
    }
}

template <class T>
void max_heapify(T* a, int i, int n) {
    while (true) {
        int left_ = left(i);
        int right_ = right(i);
        int largest = i;

        if (left_ < n && a[left_] > a[i]) {
            largest = left_;
        }
        if (right_ < n && a[right_] > a[largest]) {
            largest = right_;
        }

        if (largest == i) {
            break;
        }

        std::swap(a[i], a[largest]);
        i = largest;
    }
}

template <class T>
void heapify(T* a, int i, int n, Type type) {
    if (type == Type::MIN) {
        min_heapify(a, i, n);
    } else if (type == Type::MAX) {
        max_heapify(a, i, n);
    }
}

template <class T>
void build_heap(T* a, int n, Type type) {
    for (int i = parent(n - 1); i >= 0; --i) {
        if (type == Type::MIN) {
            min_heapify(a, i, n);
        } else if (type == Type::MAX) {
            max_heapify(a, i, n);
        }
    }
}

}
}
}
}

#endif
