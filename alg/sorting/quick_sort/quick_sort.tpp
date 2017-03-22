namespace alg {

template <class T>
void quick_sort(T *a, int n, QSPartitionStrategy st) {
    quick_sort(a, 0, n - 1, st);
}

template <class T>
void quick_sort(T *a, int p, int r, QSPartitionStrategy st) {
    if (p >= r) {
        return;
    }

    int q;

    if (st == LOMUTO) {
        q = qs_partition_lomuto(a, p, r);
    } else if (st == RANDOMIZED) {
        q = qs_partition_randomized(a, p, r);
    }

    quick_sort(a, p, q - 1, st);
    quick_sort(a, q + 1, r, st);
}

template <class T>
int qs_partition_lomuto(T *a, int p, int r) {
    int i = p - 1;

    for (int j = p; j < r; j++) {
        if (a[j] <= a[r]) {
            swap(a[++i], a[j]);
        }
    }

    swap(a[++i], a[r]);

    return i;
}

template <class T>
int qs_partition_randomized(T *a, int p, int r) {
    int i = randomizer::uniform_int(p, r);
    swap(a[i], a[r]);

    return qs_partition_lomuto(a, p, r);
}

}
