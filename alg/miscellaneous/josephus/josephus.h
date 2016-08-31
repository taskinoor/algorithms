#ifndef ALG_JOSEPHUS_H_
#define ALG_JOSEPHUS_H_

#include <algorithm>
#include <random>

#include "order_statistic_tree.h"

namespace alg {

int josephus_queue(int n, int k);
int josephus_ost(int n, int k);

OrderStatisticTree<int> *_get_randomized_ost(int n);

}

#endif
