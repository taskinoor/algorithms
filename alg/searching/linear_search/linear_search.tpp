namespace alg {

template <class T>
int linear_search(T *a, T key, std::size_t n) {
    for (int i = 0; i < n; i++) {
        if (a[i] == key) {
            return i;
        }
    }

    return -1;
}

}
