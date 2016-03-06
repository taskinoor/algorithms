#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdexcept>

class QueueFullError : public std::runtime_error {
public:
    QueueFullError() : std::runtime_error("Queue is full") {}
};

class QueueEmptyError : public std::runtime_error {
public:
    QueueEmptyError() : std::runtime_error("Queue is empty") {}
};

#endif
