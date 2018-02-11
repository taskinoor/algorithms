#ifndef ALG_DS_TREE_TRAVERSAL_INORDER_H_
#define ALG_DS_TREE_TRAVERSAL_INORDER_H_

#include "alg/common/iterator.h"
#include "alg/data_structure/stack.h"
#include "alg/data_structure/tree/binary_tree.h"

namespace alg {
namespace ds {
namespace tree {
namespace traversal {

template <class T>
class InOrderIterator : public patterns::Iterator<T> {
public:
    explicit InOrderIterator(BinaryTree<T>* tree);
    virtual ~InOrderIterator();

    void first();
    void next();
    bool is_done() const;

    T current_item() const;
    Node<T>* current_node() const;

private:
    BinaryTree<T>* tree;
    Stack<Node<T>*>* stack;

    void push_left_nodes(Node<T>* p);
};

template <class T>
InOrderIterator<T>::InOrderIterator(BinaryTree<T>* tree) {
    this->tree = tree;
    stack = new Stack<Node<T>*>(256);
}

template <class T>
InOrderIterator<T>::~InOrderIterator() {
    delete stack;
}

template <class T>
void InOrderIterator<T>::push_left_nodes(Node<T>* p) {
    while (p != tree->nil()) {
        stack->push(p);
        p = tree->left(p);
    }
}

template <class T>
void InOrderIterator<T>::first() {
    push_left_nodes(tree->root());
}

template <class T>
void InOrderIterator<T>::next() {
    Node<T>* p = stack->pop();
    push_left_nodes(tree->right(p));
}

template <class T>
bool InOrderIterator<T>::is_done() const {
    return !stack->count();
}

template <class T>
T InOrderIterator<T>::current_item() const {
    return stack->top()->element();
}

template <class T>
Node<T>* InOrderIterator<T>::current_node() const {
    return stack->top();
}

}
}
}
}

#endif
