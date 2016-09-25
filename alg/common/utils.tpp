namespace alg {

template <class T>
T max(const T& a, const T& b) {
    return a > b ? a : b;
}

template <class T>
int min_index(T *a, std::size_t n, int start) {
    int index = start;
    T value = a[index];

    for (int i = start + 1; i < n; i++) {
        if (a[i] < value) {
            index = i;
            value = a[index];
        }
    }

    return index;
}

template <class T>
void swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

}
