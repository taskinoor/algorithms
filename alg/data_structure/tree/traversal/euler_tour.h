#ifndef ALG_DS_TREE_TRAVERSAL_EULER_TOUR_H_
#define ALG_DS_TREE_TRAVERSAL_EULER_TOUR_H_

#include <sstream>
#include <string>

#include "alg/data_structure/tree/binary_tree.h"

namespace alg {
namespace ds {
namespace tree {
namespace traversal {

template <class T>
void euler_visit(const Node<T>* v, std::string &out) {
    std::ostringstream buf;

    buf << v->element();
    out += buf.str();
}

template <class T>
void euler_tour(const BinaryTree<T>* tree, const Node<T>* v, std::string &out) {
    if (v == tree->nil()) {
        return;
    }

    euler_visit(v, out);
    euler_tour(tree, tree->left(v), out);
    euler_visit(v, out);
    euler_tour(tree, tree->right(v), out);
    euler_visit(v, out);
}

template <class T>
std::string euler_tour(const BinaryTree<T>* tree) {
    std::string out = "";

    euler_tour(tree, tree->root(), out);

    return out;
}

}
}
}
}

#endif
