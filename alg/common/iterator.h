#ifndef ITERATOR_H_
#define ITERATOR_H_

template <class T>
class Iterator {
public:
    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool is_done() const = 0;
    virtual T current_item() const = 0;
};

#endif
