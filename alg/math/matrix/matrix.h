#ifndef ALG_MATRIX_H_
#define ALG_MATRIX_H_

#include <cstddef>
#include <initializer_list>
#include <utility>

namespace alg {

/**
 * This Matrix class doesn't validate arguments. For example, it doesn't
 * check whether the dimensions of two matrices that we are trying to add
 * are same, or the matrices can be multiplied.
 *
 * The behavior is undefined for such dimension mismatch.
 */
template <class T>
class Matrix {
private:
    std::size_t m;
    std::size_t n;
    T *a;

public:
    Matrix(std::size_t m, std::size_t n);
    Matrix(std::initializer_list<std::initializer_list<T>> matrix_list);

    Matrix(const Matrix<T>& that);
    Matrix(Matrix<T>&& that) noexcept;

    virtual ~Matrix();

    std::pair<std::size_t, std::size_t> dimension() const;
    Matrix<T> transpose() const;

    class Proxy {
    private:
        T *a;

    public:
        Proxy(T *a);
        T& operator[](int index) const;
    };

    Proxy operator[](int index) const;

    Matrix<T>& operator=(const Matrix<T>& that);
    Matrix<T>& operator=(Matrix<T>&& that) noexcept;

    Matrix<T> operator+(const Matrix<T>& that) const;
    Matrix<T> operator-(const Matrix<T>& that) const;
    Matrix<T> operator*(const Matrix<T>& that) const;
    Matrix<T> operator*(const T& lambda) const;
};

template <class T>
Matrix<T> operator*(const T& lambda, const Matrix<T>& M);

}

#include "matrix.tpp"

#endif
