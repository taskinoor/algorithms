#ifndef ALG_PRIORITY_QUEUE_H_
#define ALG_PRIORITY_QUEUE_H_

#include <cstddef>
#include <limits>

#include "alg/common/utils.h"
#include "alg/data_structure/extendable_array/array.h"
#include "alg/data_structure/heap/binary/binary_heap.h"
#include "alg/data_structure/queue/queue.h"

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

        PQData() {}
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

}

#include "priority_queue.tpp"

#endif
