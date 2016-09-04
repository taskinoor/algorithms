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

}

#include "queue.tpp"

#endif
