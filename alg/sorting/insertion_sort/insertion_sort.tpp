namespace alg {

template <class T>
void insertion_sort(T *a, std::size_t n) {
    for (int j = 1; j < n; j++) {
        T key = a[j];
        int i = j - 1;

        while (i >= 0 && a[i] > key) {
            a[i + 1] = a[i];
            i--;
        }

        a[i + 1] = key;
    }
}

}
