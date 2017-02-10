#include <gtest/gtest.h>

#include "alg/math/matrix/matrix.h"

namespace algtest {

TEST(Matrix, Dimension) {
    alg::Matrix<double> A(17, 13);

    std::pair<std::size_t, std::size_t> d = A.dimension();

    ASSERT_EQ(17, d.first);
    ASSERT_EQ(13, d.second);
}

TEST(Matrix, SubscriptOperator) {
    std::size_t m = 5;
    std::size_t n = 7;
    alg::Matrix<int> A(m, n);

    for (std::size_t i = 0; i < m; i++) {
        for (std::size_t j = 0; j < n; j++) {
            A[i][j] = i + j;
        }
    }

    for (std::size_t i = 0; i < m; i++) {
        for (std::size_t j = 0; j < n; j++) {
            ASSERT_EQ(i + j, A[i][j]);
        }
    }
}

TEST(Matrix, InitializerList) {
    constexpr std::size_t m = 2;
    constexpr std::size_t n = 3;

    alg::Matrix<int> A = {
        {2, 3, 5},
        {7, 11, 13}
    };
    int expected[m][n] = {
        {2, 3, 5},
        {7, 11, 13}
    };

    std::pair<std::size_t, std::size_t> d = A.dimension();

    ASSERT_EQ(m, d.first);
    ASSERT_EQ(n, d.second);

    for (std::size_t i = 0; i < m; i++) {
        for (std::size_t j = 0; j < n; j++) {
            ASSERT_EQ(expected[i][j], A[i][j]);
        }
    }
}

template <class T>
alg::Matrix<T> matrix_test_helper(alg::Matrix<T> A) {
    return A;
}

TEST(Matrix, CopyAndMoveConstructor) {
    alg::Matrix<int> A = {{2, 5}};
    alg::Matrix<int> B = matrix_test_helper(A);
    std::pair<std::size_t, std::size_t> d = B.dimension();

    B[0][0] = 3;

    ASSERT_EQ(2, A[0][0]);
    ASSERT_EQ(3, B[0][0]);
    ASSERT_EQ(5, B[0][1]);
    ASSERT_EQ(1, d.first);
    ASSERT_EQ(2, d.second);
}

TEST(Matrix, CopyAssignmentOperator) {
    alg::Matrix<double> A = {{2.3}};
    alg::Matrix<double> B = {{5.7}};

    B = A;
    A[0][0] = 11.13;

    ASSERT_DOUBLE_EQ(11.13, A[0][0]);
    ASSERT_DOUBLE_EQ(2.3, B[0][0]);
}

TEST(Matrix, MoveAssignmentOperator) {
    alg::Matrix<double> A = {{2.3}};
    alg::Matrix<double> B = {{5.7}};

    B = std::move(A);

    ASSERT_DOUBLE_EQ(2.3, B[0][0]);
}

TEST(Matrix, Transpose) {
    constexpr std::size_t m = 2;
    constexpr std::size_t n = 3;

    alg::Matrix<int> A = {
        {1, 2, 3},
        {4, 5, 6}
    };
    int expected[n][m] = {
        {1, 4},
        {2, 5},
        {3, 6}
    };
    alg::Matrix<int> AT = A.transpose();
    std::pair<std::size_t, std::size_t> d = AT.dimension();

    ASSERT_EQ(n, d.first);
    ASSERT_EQ(m, d.second);

    for (std::size_t i = 0; i < n; i++) {
        for (std::size_t j = 0; j < m; j++) {
            ASSERT_EQ(expected[i][j], AT[i][j]);
        }
    }
}

}
