#include <functional>
#include <queue>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "alg/common/exception.h"
#include "alg/common/randomizer.h"
#include "alg/data_structure/priority_queue.h"

namespace algtest {

TEST(PriorityQueue, MaxQueue) {
    alg::ds::PriorityQueue<std::string> queue(alg::ds::PriorityQueueType::MAX);

    ASSERT_EQ(0, queue.count());

    ASSERT_THROW(queue.top(), alg::except::BufferEmpty);
    ASSERT_THROW(queue.pop(), alg::except::BufferEmpty);

    queue.insert("2", 2);

    ASSERT_EQ(1, queue.count());
    ASSERT_EQ("2", queue.top());
    ASSERT_EQ("2", queue.pop());
    ASSERT_EQ(0, queue.count());

    queue.insert("7", 7);
    queue.insert("-1", -1);
    queue.insert("5", 5);

    ASSERT_EQ(3, queue.count());
    ASSERT_EQ("7", queue.pop());
    ASSERT_EQ("5", queue.pop());
    ASSERT_EQ("-1", queue.pop());
    ASSERT_EQ(0, queue.count());

    ASSERT_THROW(queue.top(), alg::except::BufferEmpty);
    ASSERT_THROW(queue.pop(), alg::except::BufferEmpty);
}

TEST(PriorityQueue, MinQueue) {
    alg::ds::PriorityQueue<std::string> queue(alg::ds::PriorityQueueType::MIN);

    ASSERT_EQ(0, queue.count());

    ASSERT_THROW(queue.top(), alg::except::BufferEmpty);
    ASSERT_THROW(queue.pop(), alg::except::BufferEmpty);

    queue.insert("2", 2);

    ASSERT_EQ(1, queue.count());
    ASSERT_EQ("2", queue.top());
    ASSERT_EQ("2", queue.pop());
    ASSERT_EQ(0, queue.count());

    queue.insert("7", 7);
    queue.insert("-1", -1);
    queue.insert("5", 5);

    ASSERT_EQ(3, queue.count());
    ASSERT_EQ("-1", queue.pop());
    ASSERT_EQ("5", queue.pop());
    ASSERT_EQ("7", queue.pop());
    ASSERT_EQ(0, queue.count());

    ASSERT_THROW(queue.top(), alg::except::BufferEmpty);
    ASSERT_THROW(queue.pop(), alg::except::BufferEmpty);
}

TEST(PriorityQueue, MaxQueueLargeDataSet) {
    constexpr int total = 500000;
    std::priority_queue<int> std_queue;
    alg::ds::PriorityQueue<int> alg_queue(alg::ds::PriorityQueueType::MAX);

    for (int i = 1; i <= total; ++i) {
        int data = alg::randomizer::uniform_int(-100000, 100000);

        std_queue.push(data);
        alg_queue.insert(data, data);

        if (!(i % 3)) {
            int popped_data = std_queue.top();
            std_queue.pop();

            ASSERT_EQ(popped_data, alg_queue.pop());
        }

        ASSERT_EQ(std_queue.top(), alg_queue.top());
        ASSERT_EQ(std_queue.size(), alg_queue.count());
    }

    while (std_queue.size() > 0) {
        int std_popped_data = std_queue.top();
        std_queue.pop();
        int alg_popped_data = alg_queue.pop();

        ASSERT_EQ(std_popped_data, alg_popped_data);
        ASSERT_EQ(std_queue.size(), alg_queue.count());
    }
}

TEST(PriorityQueue, MinQueueLargeDataSet) {
    constexpr int total = 500000;
    std::priority_queue<int, std::vector<int>, std::greater<int>> std_queue;
    alg::ds::PriorityQueue<int> alg_queue(alg::ds::PriorityQueueType::MIN);

    for (int i = 1; i <= total; ++i) {
        int data = alg::randomizer::uniform_int(-100000, 100000);

        std_queue.push(data);
        alg_queue.insert(data, data);

        if (!(i % 3)) {
            int popped_data = std_queue.top();
            std_queue.pop();

            ASSERT_EQ(popped_data, alg_queue.pop());
        }

        ASSERT_EQ(std_queue.top(), alg_queue.top());
        ASSERT_EQ(std_queue.size(), alg_queue.count());
    }

    while (std_queue.size() > 0) {
        int std_popped_data = std_queue.top();
        std_queue.pop();
        int alg_popped_data = alg_queue.pop();

        ASSERT_EQ(std_popped_data, alg_popped_data);
        ASSERT_EQ(std_queue.size(), alg_queue.count());
    }
}

}
