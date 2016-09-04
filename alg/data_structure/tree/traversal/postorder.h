#ifndef ALG_POSTORDER_H_
#define ALG_POSTORDER_H_

#include "binary_tree.h"
#include "iterator.h"
#include "stack.h"

namespace alg {

template <class T>
class PostOrderIterator : public Iterator<T> {
private:
    BinaryTree<T> *tree;
    Stack<TreeNode<T> *> *stack;
    TreeNode<T> *last_visited;

public:
    PostOrderIterator(BinaryTree<T> *tree);
    virtual ~PostOrderIterator();

    void first();
    void next();
    bool is_done() const;
    T current_item() const;
};

}

#include "postorder.tpp"

#endif
