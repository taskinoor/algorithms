#ifndef ALG_INORDER_H_
#define ALG_INORDER_H_

#include "alg/common/iterator.h"
#include "alg/data_structure/stack.h"
#include "alg/data_structure/tree/binary_tree.h"

namespace alg {

template <class T>
class InOrderIterator : public Iterator<T> {
public:
    InOrderIterator(BinaryTree<T> *tree);
    virtual ~InOrderIterator();

    void first();
    void next();
    bool is_done() const;

    T current_item() const;
    TreeNode<T> *current_node() const;

private:
    BinaryTree<T> *tree;
    Stack<TreeNode<T> *> *stack;

    void push_left_nodes(TreeNode<T> *p);
};

template <class T>
InOrderIterator<T>::InOrderIterator(BinaryTree<T> *tree) {
    this->tree = tree;
    stack = new Stack<TreeNode<T> *>(256);
}

template <class T>
InOrderIterator<T>::~InOrderIterator() {
    delete stack;
}

template <class T>
void InOrderIterator<T>::push_left_nodes(TreeNode<T> *p) {
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
    TreeNode<T> *p = stack->pop();
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
TreeNode<T> *InOrderIterator<T>::current_node() const {
    return stack->top();
}

}

#endif
