#ifndef EULER_TOUR_H_
#define EULER_TOUR_H_

#include <iostream>

#include "binary_tree.h"

template <class T>
void visit(Node<T> *);

template <class T>
void euler_tour(BinaryTree<T> *);

template <class T>
void euler_tour(BinaryTree<T> *, Node<T> *);

#include "euler_tour.tpp"

#endif
