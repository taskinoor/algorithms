namespace alg {

template <class T>
void heap_sort(T *a, int n) {
    heap::binary::build_heap(a, n, heap::binary::MAX_HEAP);

    while (n > 1) {
        swap(a[0], a[n - 1]);
        n--;
        heap::binary::max_heapify(a, 0, n);
    }
}

}
