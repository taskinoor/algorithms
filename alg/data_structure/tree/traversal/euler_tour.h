#ifndef ALG_EULER_TOUR_H_
#define ALG_EULER_TOUR_H_

#include <sstream>
#include "binary_tree.h"

namespace alg {

template <class T>
void euler_visit(TreeNode<T> *v, std::string &out);

template <class T>
std::string euler_tour(BinaryTree<T> *tree);

template <class T>
void euler_tour(BinaryTree<T> *tree, TreeNode<T> *v, std::string &out);

}

#include "euler_tour.tpp"

#endif
