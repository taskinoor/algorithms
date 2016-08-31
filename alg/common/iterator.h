#ifndef ALG_ITERATOR_H_
#define ALG_ITERATOR_H_

namespace alg {

template <class T>
class Iterator {
public:
    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool is_done() const = 0;
    virtual T current_item() const = 0;
};

}

#endif
