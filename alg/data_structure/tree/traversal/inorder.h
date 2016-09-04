#ifndef ALG_INORDER_H_
#define ALG_INORDER_H_

#include "iterator.h"
#include "stack.h"
#include "binary_tree.h"

namespace alg {

template <class T>
class InOrderIterator : public Iterator<T> {
private:
    BinaryTree<T> *tree;
    Stack<TreeNode<T> *> *stack;

    void push_left_nodes(TreeNode<T> *);
public:
    InOrderIterator(BinaryTree<T> *);
    ~InOrderIterator();

    virtual void first();
    virtual void next();
    virtual bool is_done() const;
    virtual T current_item() const;
};

}

#include "inorder.tpp"

#endif