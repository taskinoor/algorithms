#ifndef ALG_PRIORITY_QUEUE_H_
#define ALG_PRIORITY_QUEUE_H_

#include <cstddef>
#include <limits>

#include "alg/common/utils.h"
#include "alg/data_structure/array.h"
#include "alg/data_structure/binary_heap.h"
#include "alg/data_structure/queue.h"

namespace alg {

enum class PriorityQueueType {
    MIN,
    MAX
};

template <class T>
class PriorityQueue {
private:
    class PQData {
    public:
        T element;
        int priority;

        PQData() : element{T()}, priority{0} {}
        PQData(const T& element, int priority) :
            element{element}, priority{priority} {}

        bool operator<(const PQData& that) {
            return priority < that.priority;
        }

        bool operator>(const PQData& that) {
            return priority > that.priority;
        }
    };

    PriorityQueueType type;
    ExtendableArray<PQData> buffer;
    std::size_t count_;

    void increase_priority(int index, int new_priority);
    void decrease_priority(int index, int new_priority);

public:
    PriorityQueue(PriorityQueueType type);

    T top();
    T pop();

    void insert(const T& element, int priority);
    void update_priority(int index, int new_priority);

    std::size_t count() const;
};

template <class T>
PriorityQueue<T>::PriorityQueue(PriorityQueueType type)
    : type{type},
      count_{0} {
}

template <class T>
std::size_t PriorityQueue<T>::count() const {
    return count_;
}

template <class T>
T PriorityQueue<T>::top() {
    if (!count_) {
        throw QueueEmptyError();
    }

    return buffer[0].element;
}

template <class T>
T PriorityQueue<T>::pop() {
    if (!count_) {
        throw QueueEmptyError();
    }

    T element = buffer[0].element;
    buffer[0] = buffer[count_ - 1];
    count_--;

    heap::binary::HeapType heap_type = (type == PriorityQueueType::MIN) ?
            heap::binary::HeapType::MIN : heap::binary::HeapType::MAX;

    heap::binary::heapify(buffer.data_ptr(), 0, count_, heap_type);

    return element;
}

template <class T>
void PriorityQueue<T>::insert(const T& element, int priority) {
    int default_priotiry = (type == PriorityQueueType::MAX) ?
            std::numeric_limits<int>::min() : std::numeric_limits<int>::max();

    PQData data(element, default_priotiry);
    count_++;

    if (count_ <= buffer.count()) {
        buffer[count_ - 1] = data;
    } else {
        buffer.add(count_ - 1, data);
    }

    update_priority(count_ - 1, priority);
}

template <class T>
void PriorityQueue<T>::update_priority(int index, int new_priority) {
    if (type == PriorityQueueType::MIN) {
        decrease_priority(index, new_priority);
    } else {
        increase_priority(index, new_priority);
    }
}

template <class T>
void PriorityQueue<T>::increase_priority(int index, int new_priority) {
    if (new_priority <= buffer[index].priority) {
        return;
    }

    buffer[index].priority = new_priority;

    while (index > 0) {
        int parent = heap::binary::parent(index);

        if (buffer[index].priority <= buffer[parent].priority) {
            break;
        }

        swap(buffer[index], buffer[parent]);
        index = parent;
    }
}

template <class T>
void PriorityQueue<T>::decrease_priority(int index, int new_priority) {
    if (new_priority >= buffer[index].priority) {
        return;
    }

    buffer[index].priority = new_priority;

    while (index > 0) {
        int parent = heap::binary::parent(index);

        if (buffer[index].priority >= buffer[parent].priority) {
            break;
        }

        swap(buffer[index], buffer[parent]);
        index = parent;
    }
}

}

#endif
