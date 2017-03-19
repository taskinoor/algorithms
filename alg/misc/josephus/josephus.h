#ifndef ALG_JOSEPHUS_H_
#define ALG_JOSEPHUS_H_

#include <algorithm>

#include "alg/common/randomizer.h"
#include "alg/data_structure/tree/order_statistic_tree/order_statistic_tree.h"

namespace alg {

int josephus_queue(int n, int k);
int josephus_ost(int n, int k);

OrderStatisticTree<int> *randomized_ost(int n);

}

#endif
