#ifndef ALG_MERGE_SORT_H_
#define ALG_MERGE_SORT_H_

namespace alg {

template <class T>
void merge(T *a, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    T *left = new T[n1];
    T *right = new T[n2];

    for (int i = 0; i < n1; i++) {
        left[i] = a[p + i];
    }
    for (int i = 0; i < n2; i++) {
        right[i] = a[q + 1 + i];
    }

    for (int i = 0, j = 0, k = p; k <= r; k++) {
        if (i == n1) {
            a[k] = right[j];
            j++;
        } else if (j == n2) {
            a[k] = left[i];
            i++;
        } else if (left[i] <= right[j]) {
            a[k] = left[i];
            i++;
        } else {
            a[k] = right[j];
            j++;
        }
    }

    delete[] left;
    delete[] right;
}

template <class T>
void merge_sort(T *a, int p, int r) {
    if (p >= r) {
        return;
    }

    int q = (p + r) / 2;

    merge_sort(a, p, q);
    merge_sort(a, q + 1, r);
    merge(a, p, q, r);
}

template <class T>
void merge_sort(T *a, int n) {
    merge_sort(a, 0, n - 1);
}

}

#endif
