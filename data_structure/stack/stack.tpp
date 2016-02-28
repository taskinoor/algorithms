# include "stack.h"

template <class T>
Stack<T>::Stack(size_t n) {
    size = n;
    top = -1;
    buffer = new T[n];
}

template <class T>
Stack<T>::~Stack() {
    delete[] buffer;
}

template <class T>
void Stack<T>::push(T element) {
    if (top == size - 1) {
        throw StackFullError();
    }

    top += 1;
    buffer[top] = element;
}

template <class T>
T Stack<T>::pop() {
    if (top == -1) {
        throw StackEmptyError();
    }

    T element = buffer[top];
    top -= 1;

    return element;
}
