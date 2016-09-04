#ifndef ALG_PREORDER_H_
#define ALG_PREORDER_H_

#include "binary_tree.h"
#include "iterator.h"
#include "stack.h"

namespace alg {

template <class T>
class PreOrderIterator : public Iterator<T> {
private:
    BinaryTree<T> *tree;
    Stack<TreeNode<T> *> *stack;

public:
    PreOrderIterator(BinaryTree<T> *tree);
    virtual ~PreOrderIterator();

    void first();
    void next();
    bool is_done() const;
    T current_item() const;
};

}

#include "preorder.tpp"

#endif
