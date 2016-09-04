#ifndef ALG_EULER_TOUR_H_
#define ALG_EULER_TOUR_H_

#include <iostream>
#include "binary_tree.h"

namespace alg {

template <class T>
void visit(TreeNode<T> *v);

template <class T>
void euler_tour(BinaryTree<T> *tree);

template <class T>
void euler_tour(BinaryTree<T> *tree, TreeNode<T> *v);

}

#include "euler_tour.tpp"

#endif
