#ifndef ALG_PREORDER_H_
#define ALG_PREORDER_H_

#include "iterator.h"
#include "stack.h"
#include "binary_tree.h"

namespace alg {

template <class T>
class PreOrderIterator : public Iterator<T> {
private:
    BinaryTree<T> *tree;
    Stack<TreeNode<T> *> *stack;
public:
    PreOrderIterator(BinaryTree<T> *);
    ~PreOrderIterator();

    virtual void first();
    virtual void next();
    virtual bool is_done() const;
    virtual T current_item() const;
};

}

#include "preorder.tpp"

#endif
