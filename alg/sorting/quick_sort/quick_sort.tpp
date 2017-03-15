namespace alg {

template <class T>
void quick_sort(T *a, int n) {
    quick_sort(a, 0, n - 1);
}

template <class T>
void quick_sort(T *a, int p, int r) {
    if (p >= r) {
        return;
    }

    int q = qs_partition(a, p, r);
    quick_sort(a, p, q - 1);
    quick_sort(a, q + 1, r);
}

template <class T>
int qs_partition(T *a, int p, int r) {
    int i = p - 1;

    for (int j = p; j < r; j++) {
        if (a[j] <= a[r]) {
            swap(a[++i], a[j]);
        }
    }

    swap(a[++i], a[r]);

    return i;
}

}
