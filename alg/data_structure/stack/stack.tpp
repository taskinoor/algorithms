namespace alg {

template <class T>
Stack<T>::Stack(std::size_t n) {
    size = n;
    top_ = -1;
    buffer = new T[n];
}

template <class T>
Stack<T>::~Stack() {
    delete[] buffer;
}

template <class T>
void Stack<T>::push(T element) {
    if (top_ == size - 1) {
        throw StackFullError();
    }

    top_++;
    buffer[top_] = element;
}

template <class T>
T Stack<T>::pop() {
    if (top_ == -1) {
        throw StackEmptyError();
    }

    top_--;
    return buffer[top_ + 1];
}

template <class T>
T Stack<T>::top() {
    if (top_ == -1) {
        throw StackEmptyError();
    }

    return buffer[top_];
}

template <class T>
std::size_t Stack<T>::count() {
    return top_ + 1;
}

}
