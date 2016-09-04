#ifndef ALG_INORDER_H_
#define ALG_INORDER_H_

#include "binary_tree.h"
#include "iterator.h"
#include "stack.h"

namespace alg {

template <class T>
class InOrderIterator : public Iterator<T> {
private:
    BinaryTree<T> *tree;
    Stack<TreeNode<T> *> *stack;

    void push_left_nodes(TreeNode<T> *p);

public:
    InOrderIterator(BinaryTree<T> *tree);
    virtual ~InOrderIterator();

    void first();
    void next();
    bool is_done() const;
    T current_item() const;
};

}

#include "inorder.tpp"

#endif
