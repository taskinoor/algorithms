#ifndef PREORDER_H_
#define PREORDER_H_

#include "iterator.h"
#include "stack.h"
#include "binary_tree.h"

template <class T>
class PreOrderIterator : public Iterator<T> {
private:
    BinaryTree<T> *tree;
    Stack<Node<T> *> *stack;
public:
    PreOrderIterator(BinaryTree<T> *);
    ~PreOrderIterator();

    virtual void first();
    virtual void next();
    virtual bool is_done() const;
    virtual T current_item() const;
};

#include "preorder.tpp"

#endif
