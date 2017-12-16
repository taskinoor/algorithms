#ifndef ALGTEST_HELPER_H_
#define ALGTEST_HELPER_H_

namespace algtest {

template <class T>
class NoDefaultCtor {
public:
    NoDefaultCtor(const T& data) {
        data_ = new T;
        *data_ = data;
    }

    NoDefaultCtor(const NoDefaultCtor<T>& rhs) {
        data_ = new T;
        *data_ = rhs.data();
    }

    NoDefaultCtor<T>& operator=(const NoDefaultCtor<T>& rhs) {
        *data_ = rhs.data();

        return *this;
    }

    bool operator==(const NoDefaultCtor<T>& rhs) const {
        return *data_ == rhs.data();
    }

    ~NoDefaultCtor() {
        delete data_;
    }

    T data() const {
        return *data_;
    }

private:
    T* data_{nullptr};
};

}

#endif
