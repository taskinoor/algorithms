#ifndef ALG_DS_PRIORITY_QUEUE_H_
#define ALG_DS_PRIORITY_QUEUE_H_

#include <cstddef>
#include <cstdint>

#include <algorithm>
#include <limits>

#include "alg/common/exception.h"
#include "alg/data_structure/binary_heap.h"
#include "alg/data_structure/extendable_array.h"

namespace alg {
namespace ds {

enum class PriorityQueueType {
    MIN,
    MAX
};

template <class T>
class PriorityQueue {
public:
    explicit PriorityQueue(PriorityQueueType type);

    T top();
    T pop();

    void insert(const T& element, std::uint32_t priority);
    void update_priority(std::size_t index, std::uint32_t new_priority);

    std::size_t count() const;

private:
    class PQData {
    public:
        T element;
        std::uint32_t priority;

        PQData(const T& element, std::uint32_t priority) :
            element{element}, priority{priority} {}

        bool operator<(const PQData& rhs) const {
            return priority < rhs.priority;
        }

        bool operator>(const PQData& rhs) const {
            return priority > rhs.priority;
        }
    };

    PriorityQueueType type;
    ExtendableArray<PQData> buffer;
    std::size_t count_;

    void increase_priority(std::size_t index, std::uint32_t new_priority);
    void decrease_priority(std::size_t index, std::uint32_t new_priority);
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
        throw except::BufferEmpty();
    }

    return buffer[0].element;
}

template <class T>
T PriorityQueue<T>::pop() {
    if (!count_) {
        throw except::BufferEmpty();
    }

    T element = buffer[0].element;
    buffer[0] = buffer[count_ - 1];
    --count_;

    heap::binary::Type heap_type = (type == PriorityQueueType::MIN) ?
            heap::binary::Type::MIN : heap::binary::Type::MAX;

    heap::binary::heapify(buffer.data_ptr(), 0, count_, heap_type);

    return element;
}

template <class T>
void PriorityQueue<T>::insert(const T& element, std::uint32_t priority) {
	std::uint32_t default_priotiry = (type == PriorityQueueType::MAX) ?
            std::numeric_limits<std::uint32_t>::min() :
            std::numeric_limits<std::uint32_t>::max();

    PQData data(element, default_priotiry);
    ++count_;

    if (count_ <= buffer.count()) {
        buffer[count_ - 1] = data;
    } else {
        buffer.add(count_ - 1, data);
    }

    update_priority(count_ - 1, priority);
}

template <class T>
void PriorityQueue<T>::update_priority(std::size_t index,
		std::uint32_t new_priority) {

    if (type == PriorityQueueType::MIN) {
        decrease_priority(index, new_priority);
    } else {
        increase_priority(index, new_priority);
    }
}

template <class T>
void PriorityQueue<T>::increase_priority(std::size_t index,
		std::uint32_t new_priority) {

    if (new_priority <= buffer[index].priority) {
        return;
    }

    buffer[index].priority = new_priority;

    while (index > 0) {
        int parent = heap::binary::parent(index);

        if (buffer[index].priority <= buffer[parent].priority) {
            break;
        }

        std::swap(buffer[index], buffer[parent]);
        index = parent;
    }
}

template <class T>
void PriorityQueue<T>::decrease_priority(std::size_t index,
		std::uint32_t new_priority) {

    if (new_priority >= buffer[index].priority) {
        return;
    }

    buffer[index].priority = new_priority;

    while (index > 0) {
        int parent = heap::binary::parent(index);

        if (buffer[index].priority >= buffer[parent].priority) {
            break;
        }

        std::swap(buffer[index], buffer[parent]);
        index = parent;
    }
}

}
}

#endif
