#ifndef INORDER_H_
#define INORDER_H_

#include "iterator.h"
#include "stack.h"
#include "binary_tree.h"

template <class T>
class InOrderIterator : public Iterator<T> {
private:
    BinaryTree<T> *tree;
    Stack<Node<T> *> *stack;

    void push_left_nodes(Node<T> *);
public:
    InOrderIterator(BinaryTree<T> *);
    ~InOrderIterator();

    virtual void first();
    virtual void next();
    virtual bool is_done() const;
    virtual T current_item() const;
};

#include "inorder.tpp"

#endif
