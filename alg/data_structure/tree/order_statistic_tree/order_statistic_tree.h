#ifndef ALG_ORDER_STATISTIC_TREE_H_
#define ALG_ORDER_STATISTIC_TREE_H_

#include "alg/data_structure/tree/binary_search_tree/bst.h"

namespace alg {

template <class T> class OrderStatisticTree;

template <class T>
class OSTNode : public TreeNode<T> {
private:
    int count_;

    friend class OrderStatisticTree<T>;

public:
    OSTNode(T element = T());

    int count();
};

template <class T>
class OrderStatisticTree : public BST<T> {
private:
    void decrement_count(OSTNode<T> *node, OSTNode<T> *until);

public:
    void insert(T element) override;
    void remove(TreeNode<T> *z) override;

    T select(int i);
    T select(int i, OSTNode<T> *v);

    TreeNode<T> *select_node(int i);
    TreeNode<T> *select_node(int i, OSTNode<T> *v);

    int rank(T element);
};

}

#include "order_statistic_tree.tpp"

#endif
