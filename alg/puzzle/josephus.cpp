#include <algorithm>
#include <memory>

#include "alg/common/randomizer.h"
#include "alg/data_structure/extendable_array.h"
#include "alg/data_structure/queue.h"
#include "alg/data_structure/tree/order_statistic_tree.h"

#include "josephus.h"

namespace alg {
namespace puzzle {

namespace {

std::unique_ptr<OrderStatisticTree<std::size_t>> randomized_ost(std::size_t n) {
    ExtendableArray<std::size_t> data(n);

    for (std::size_t i = 1; i <= n; ++i) {
        data.append(i);
    }

    std::shuffle(data.data_ptr(), data.data_ptr() + n, randomizer::engine());

    std::unique_ptr<OrderStatisticTree<std::size_t>> ost(
            new OrderStatisticTree<std::size_t>());

    for (std::size_t i = 0; i < n; ++i) {
        ost->insert(data[i]);
    }

    return ost;
}

}

std::size_t josephus_queue(std::size_t n, std::size_t k) {
    Queue<std::size_t> q(n);

    for (std::size_t i = 1; i <= n; ++i) {
        q.enqueue(i);
    }

    while (true) {
        for (std::size_t i = 1; i < k; ++i) {
            q.enqueue(q.dequeue());
        }

        q.dequeue();

        if (q.count() == 1) {
            return q.dequeue();
        }
    }
}

std::size_t josephus_ost(std::size_t n, std::size_t k) {
    std::unique_ptr<OrderStatisticTree<std::size_t>> ost = randomized_ost(n);

    std::size_t left = n;
    std::size_t next = (k - 1) % left;

    while (left > 1) {
        ost->remove(ost->select_node(next));
        --left;
        next = (next + k - 1) % left;
    }

    return ost->root()->element();
}

}
}
