#include "josephus.h"
#include "queue.h"

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
    OrderStatisticTree<int> *ost = _get_randomized_ost(n);
    int left = n;
    int next = (k - 1) % left;

    while (left > 1) {
        ost->remove(ost->select_node(next));
        left--;
        next = (next + k - 1) % left;
    }

    int survivor = ost->root()->get_element();
    delete ost;

    return survivor;
}

OrderStatisticTree<int> *_get_randomized_ost(int n) {
    int *data = new int[n];
    OrderStatisticTree<int> *ost = new OrderStatisticTree<int>;

    for (int i = 0; i < n; i++) {
        data[i] = i + 1;
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(&data[0], &data[n], gen);

    for (int i = 0; i < n; i++) {
        ost->insert(data[i]);
    }

    delete data;

    return ost;
}

}
