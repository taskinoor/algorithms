#ifndef ALG_MATRIX_H_
#define ALG_MATRIX_H_

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>

namespace alg {

template <class T>
class Matrix {
private:
    std::size_t m;
    std::size_t n;
    T *a;

public:
    Matrix();
    Matrix(std::size_t m, std::size_t n);
    Matrix(std::initializer_list<std::initializer_list<T>> matrix_list);

    Matrix(const Matrix<T>& that);
    Matrix(Matrix<T>&& that) noexcept;

    virtual ~Matrix();

    std::pair<std::size_t, std::size_t> dimension() const;
    Matrix<T> transpose() const;

    Matrix<T> submatrix(std::size_t start_i, std::size_t start_j,
            std::size_t x, std::size_t y) const;

    void copy(const Matrix<T>& M, std::size_t to_i, std::size_t to_j,
            std::size_t from_i, std::size_t from_j,
            std::size_t x, std::size_t y);

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
