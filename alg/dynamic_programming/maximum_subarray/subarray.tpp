template <class T>
T max_subarray(T *a, size_t n) {
    if (!n) {
        return 0;
    }

    T *suffix_sum = new T[n];

    suffix_sum[0] = MAX(0, a[0]);

    for (int i = 1; i < n; i++) {
        suffix_sum[i] = MAX(0, suffix_sum[i - 1] + a[i]);
    }

    T max = suffix_sum[0];

    for (int i = 1; i < n; i++) {
        max = MAX(max, suffix_sum[i]);
    }

    delete[] suffix_sum;

    return max;
}
