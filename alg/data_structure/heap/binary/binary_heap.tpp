namespace alg {
namespace heap {
namespace binary {

template <class T>
void build_heap(T *a, int n, Type type) {
    for (int i = parent(n - 1); i >= 0; i--) {
        if (type == MIN_HEAP) {
            min_heapify(a, i, n);
        } else {
            max_heapify(a, i, n);
        }
    }
}

template <class T>
void min_heapify(T *a, int i, int n) {
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

        swap(a[i], a[smallest]);
        i = smallest;
    }
}

template <class T>
void max_heapify(T *a, int i, int n) {
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

        swap(a[i], a[largest]);
        i = largest;
    }
}

}
}
}
