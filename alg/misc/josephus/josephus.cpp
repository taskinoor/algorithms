#include "alg/data_structure/queue/queue.h"
#include "josephus.h"

namespace alg {

int josephus_queue(int n, int k) {
    Queue<int> q(256);

    for (int i = 1; i <= n; i++) {
        q.enqueue(i);
    }

    while (true) {
        for (int i = 1; i < k; i++) {
            q.enqueue(q.dequeue());
        }
        q.dequeue();

        if (q.count() == 1) {
            return q.dequeue();
        }
    }
}

int josephus_ost(int n, int k) {
    OrderStatisticTree<int> *ost = randomized_ost(n);
    int left = n;
    int next = (k - 1) % left;

    while (left > 1) {
        ost->remove(ost->select_node(next));
        left--;
        next = (next + k - 1) % left;
    }

    int survivor = ost->root()->element();
    delete ost;

    return survivor;
}

OrderStatisticTree<int> *randomized_ost(int n) {
    int *data = new int[n];
    OrderStatisticTree<int> *ost = new OrderStatisticTree<int>;

    for (int i = 0; i < n; i++) {
        data[i] = i + 1;
    }

    std::shuffle(&data[0], &data[n], randomizer::engine());

    for (int i = 0; i < n; i++) {
        ost->insert(data[i]);
    }

    delete[] data;

    return ost;
}

}
