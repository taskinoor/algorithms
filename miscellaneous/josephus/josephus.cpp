#include "josephus.h"
#include "queue.h"

int josephus(int n, int k) {
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
