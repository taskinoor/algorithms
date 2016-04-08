template <class T>
Stack<T>::Stack(size_t n) {
    size = n;
    _top = -1;
    buffer = new T[n];
}

template <class T>
Stack<T>::~Stack() {
    delete[] buffer;
}

template <class T>
void Stack<T>::push(T element) {
    if (_top == size - 1) {
        throw StackFullError();
    }

    _top += 1;
    buffer[_top] = element;
}

template <class T>
T Stack<T>::pop() {
    if (_top == -1) {
        throw StackEmptyError();
    }

    T element = buffer[_top];
    _top -= 1;

    return element;
}

template <class T>
T Stack<T>::top() {
    if (_top == -1) {
        throw StackEmptyError();
    }

    return buffer[_top];
}

template <class T>
size_t Stack<T>::count() {
    return _top + 1;
}
