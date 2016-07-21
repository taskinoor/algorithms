#ifndef ORDER_STATISTIC_TREE_H_
#define ORDER_STATISTIC_TREE_H_

#include "bst.h"

template <class T> class OrderStatisticTree;

template <class T>
class OSTNode : public Node<T> {
    friend class OrderStatisticTree<T>;

private:
    int count;

public:
    OSTNode(T element = T());

    int get_count();
};

template <class T>
class OrderStatisticTree : public BST<T> {
private:
    void decrement_count(OSTNode<T> *node, OSTNode<T> *until);

public:
    void insert(T element) override;
    void remove(Node<T> *z) override;

    T select(int i);
    T select(int i, OSTNode<T> *v);

    int rank(T element);
};

#include "order_statistic_tree.tpp"

#endif
