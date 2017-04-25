namespace alg {

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

    heap::binary::Type heap_type = (type == PriorityQueueType::MIN) ?
            heap::binary::MIN_HEAP : heap::binary::MAX_HEAP;

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
