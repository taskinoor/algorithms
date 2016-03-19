template <class T>
ExtendableArray<T>::ExtendableArray(size_t capacity) {
    this->capacity = capacity;
    buffer = new T[capacity];
    n = 0;
}

template <class T>
ExtendableArray<T>::~ExtendableArray() {
    delete[] buffer;
}

template <class T>
void ExtendableArray<T>::grow() {
    capacity *= 2;
    T *tmp_buffer = new T[capacity];

    for (int i = 0; i < n; i++) {
        tmp_buffer[i] = buffer[i];
    }

    delete[] buffer;
    buffer = tmp_buffer;
}

template <class T>
size_t ExtendableArray<T>::count() {
    return n;
}

template <class T>
void ExtendableArray<T>::add(int index, T element) {
    if (index < 0 || index > n) {
        throw InvalidIndexError();
    }

    if (n == capacity) {
        grow();
    }

    for (int i = n - 1; i >= index; i--) {
        buffer[i + 1] = buffer[i];
    }
    buffer[index] = element;
    n++;
}

template <class T>
T ExtendableArray<T>::remove(int index) {
    if (index < 0 || index > n - 1) {
        throw InvalidIndexError();
    }

    T element = buffer[index];

    for (int i = index + 1; i < n; i++) {
        buffer[i - 1] = buffer[i];
    }
    n--;

    return element;
}

template <class T>
void ExtendableArray<T>::set(int index, T element) {
    if (index < 0 || index > n - 1) {
        throw InvalidIndexError();
    }

    buffer[index] = element;
}

template <class T>
T ExtendableArray<T>::get(int index) {
    if (index < 0 || index > n - 1) {
        throw InvalidIndexError();
    }

    return buffer[index];
}
