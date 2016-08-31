#ifndef ALG_POSTORDER_H_
#define ALG_POSTORDER_H_

#include "iterator.h"
#include "stack.h"
#include "binary_tree.h"

namespace alg {

template <class T>
class PostOrderIterator : public Iterator<T> {
private:
    BinaryTree<T> *tree;
    Stack<TreeNode<T> *> *stack;
    TreeNode<T> *last_visited;
public:
    PostOrderIterator(BinaryTree<T> *);
    ~PostOrderIterator();

    virtual void first();
    virtual void next();
    virtual bool is_done() const;
    virtual T current_item() const;
};

}

#include "postorder.tpp"

#endif
