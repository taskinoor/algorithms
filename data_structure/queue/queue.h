#ifndef QUEUE_H_
#define QUEUE_H_

#include <stddef.h>

#include <stdexcept>

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
    int front, rear;
    size_t size;
public:
    Queue(size_t);
    ~Queue();
    void enqueue(T);
    T dequeue();
};

#include "queue.tpp"

#endif
