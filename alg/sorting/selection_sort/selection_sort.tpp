namespace alg {

template <class T>
void selection_sort(T *a, int n) {
    for (int i = 0; i < n - 1; i++) {
        int index = min_index(a, n, i);

        if (index != i) {
            swap(a[index], a[i]);
        }
    }
}

}
