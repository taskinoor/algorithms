#ifndef ALG_QUEUE_H_
#define ALG_QUEUE_H_

#include <cstddef>
#include <stdexcept>

namespace alg {

class QueueFullError : public std::runtime_error {
public:
    QueueFullError() : std::runtime_error("Queue is full") {}
};

class QueueEmptyError : public std::runtime_error {
public:
    QueueEmptyError() : std::runtime_error("Queue is empty") {}
};

template <class T>
class Queue {
private:
    T *buffer;
    int front;
    int rear;
    std::size_t size;

public:
    Queue(std::size_t n);
    virtual ~Queue();

    void enqueue(T element);
    T dequeue();
    std::size_t count();
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
        throw QueueFullError();
    }

    buffer[rear] = element;
    rear = (rear + 1) % size;
}

template <class T>
T Queue<T>::dequeue() {
    if (front == rear) {
        throw QueueEmptyError();
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

#endif
