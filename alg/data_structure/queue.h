#ifndef ALG_DS_QUEUE_H_
#define ALG_DS_QUEUE_H_

#include <cstddef>

#include "alg/common/exception.h"

namespace alg {
namespace ds {

template <class T>
class Queue {
public:
    explicit Queue(std::size_t n);
    virtual ~Queue();

    void enqueue(T element);
    T dequeue();
    std::size_t count();

private:
    T* buffer;
    int front;
    int rear;
    std::size_t size;
};

template <class T>
Queue<T>::Queue(std::size_t n) {
    size = n + 1;
    buffer = new T[size];
    front = 0;
    rear = 0;
}

template <class T>
Queue<T>::~Queue() {
    delete[] buffer;
}

template <class T>
void Queue<T>::enqueue(T element) {
    if ((rear + 1) % size == front) {
        throw except::BufferFull();
    }

    buffer[rear] = element;
    rear = (rear + 1) % size;
}

template <class T>
T Queue<T>::dequeue() {
    if (front == rear) {
        throw except::BufferEmpty();
    }

    T element = buffer[front];
    front = (front + 1) % size;

    return element;
}

template <class T>
std::size_t Queue<T>::count() {
    return (rear - front + size) % size;
}

}
}

#endif
