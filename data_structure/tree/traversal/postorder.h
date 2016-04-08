#ifndef POSTORDER_H_
#define POSTORDER_H_

#include "iterator.h"
#include "stack.h"
#include "binary_tree.h"

template <class T>
class PostOrderIterator : public Iterator<T> {
private:
    BinaryTree<T> *tree;
    Stack<Node<T> *> *stack;
    Node<T> *last_visited;
public:
    PostOrderIterator(BinaryTree<T> *);
    ~PostOrderIterator();

    virtual void first();
    virtual void next();
    virtual bool is_done() const;
    virtual T current_item() const;
};

#include "postorder.tpp"

#endif
