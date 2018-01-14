#ifndef ALG_PUZZLE_JOSEPHUS_H_
#define ALG_PUZZLE_JOSEPHUS_H_

#include "alg/data_structure/tree/order_statistic_tree.h"

namespace alg {
namespace puzzle {

int josephus_queue(int n, int k);
int josephus_ost(int n, int k);

OrderStatisticTree<int>* randomized_ost(int n);

}
}

#endif
