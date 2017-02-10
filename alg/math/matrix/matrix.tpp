namespace alg {

template <class T>
Matrix<T>::Matrix(std::size_t m, std::size_t n) {
    this->m = m;
    this->n = n;
    a = new T[m * n];
}

template <class T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> matrix_list) {
    m = matrix_list.size();
    n = matrix_list.begin()->size();
    a = new T[m * n];
    int i = 0;

    for (std::initializer_list<T> row : matrix_list) {
        std::copy(row.begin(), row.end(), &a[i]);
        i += n;
    }
}

template <class T>
Matrix<T>::Matrix(const Matrix<T>& that) {
    m = that.m;
    n = that.n;
    a = new T[m * n];

    std::copy(&that.a[0], &that.a[m * n], a);
}

template <class T>
Matrix<T>::Matrix(Matrix<T>&& that) noexcept {
    m = that.m;
    n = that.n;
    a = that.a;
    that.a = nullptr;
}

template <class T>
Matrix<T>::~Matrix() {
    delete[] a;
}

template <class T>
std::pair<std::size_t, std::size_t> Matrix<T>::dimension() const {
    return {m, n};
}

template <class T>
Matrix<T> Matrix<T>::transpose() const {
    Matrix<T> M(n, m);

    for (std::size_t i = 0; i < m; i++) {
        for (std::size_t j = 0; j < n; j++) {
            M[j][i] = (*this)[i][j];
        }
    }

    return M;
}

template <class T>
Matrix<T>::Proxy::Proxy(T *a) {
    this->a = a;
}

template <class T>
T& Matrix<T>::Proxy::operator[](int index) const {
    return a[index];
}

template <class T>
typename Matrix<T>::Proxy Matrix<T>::operator[](int index) const {
    return Proxy(&a[index * n]);
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& that) {
    std::copy(&that.a[0], &that.a[m * n], a);

    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& that) noexcept {
    delete[] a;

    a = that.a;
    that.a = nullptr;

    return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& that) const {
    Matrix<T> M(m, n);

    for (std::size_t i = 0; i < m; i++) {
        for (std::size_t j = 0; j < n; j++) {
            M[i][j] = (*this)[i][j] + that[i][j];
        }
    }

    return M;
}

template <class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& that) const {
    Matrix<T> M(m, n);

    for (std::size_t i = 0; i < m; i++) {
        for (std::size_t j = 0; j < n; j++) {
            M[i][j] = (*this)[i][j] - that[i][j];
        }
    }

    return M;
}

template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& that) const {
    Matrix<T> M(m, that.n);

    for (std::size_t i = 0; i < m; i++) {
        for (std::size_t j = 0; j < that.n; j++) {
            T sum = T();

            for (std::size_t k = 0; k < n; k++) {
                sum += (*this)[i][k] * that[k][j];
            }

            M[i][j] = sum;
        }
    }

    return M;
}

}
