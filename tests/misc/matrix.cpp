#include <gtest/gtest.h>

#include "alg/misc/matrix.h"

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

TEST(Matrix, OriginalDataAfterMove) {
    alg::Matrix<int> A = {{1, 2, 3}, {4, 5, 6}};
    std::pair<std::size_t, std::size_t> dimension = {2, 3};
    std::pair<std::size_t, std::size_t> dimension_after_move = {0, 0};

    ASSERT_NE(nullptr, A.data_ptr());
    ASSERT_EQ(dimension, A.dimension());

    alg::Matrix<int> B = std::move(A);

    ASSERT_NE(nullptr, B.data_ptr());
    ASSERT_EQ(dimension, B.dimension());

    ASSERT_EQ(nullptr, A.data_ptr());
    ASSERT_EQ(dimension_after_move, A.dimension());

    alg::Matrix<int> C;

    C = std::move(B);

    ASSERT_NE(nullptr, C.data_ptr());
    ASSERT_EQ(dimension, C.dimension());

    ASSERT_EQ(nullptr, B.data_ptr());
    ASSERT_EQ(dimension_after_move, B.dimension());
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

TEST(Matrix, AdditionSubtraction) {
    constexpr std::size_t m = 3;
    constexpr std::size_t n = 4;

    alg::Matrix<int> A = {
        {2, 3, 5, 7},
        {11, 13, 17, 19},
        {23, 29, 31, 37}
    };
    alg::Matrix<int> B = {
        {41, 43, 47, 53},
        {59, 61, 67, 71},
        {73, 79, 83, 89}
    };
    alg::Matrix<int> C = {
        {97, 101, 103, 107},
        {109, 113, 127, 131},
        {137, 139, 149, 151}
    };
    alg::Matrix<int> D = {
        {157, 163, 167, 173},
        {179, 181, 191, 193},
        {197, 199, 211, 223}
    };
    int expected[m][n] = {
        {103, 108, 116, 126},
        {140, 142, 148, 152},
        {156, 168, 176, 198}
    };

    alg::Matrix<int> M = A + B - C + D;
    std::pair<std::size_t, std::size_t> d = M.dimension();

    ASSERT_EQ(m, d.first);
    ASSERT_EQ(n, d.second);

    for (std::size_t i = 0; i < m; i++) {
        for (std::size_t j = 0; j < n; j++) {
            ASSERT_EQ(expected[i][j], M[i][j]);
        }
    }
}

TEST(Matrix, Multiplication) {
    alg::Matrix<double> A = {
        {2.3, 5.7, 11.13},
        {17.19, 23.29, 31.37}
    };
    alg::Matrix<double> B = {
        {41.43, 47.53},
        {59.61, 67.71},
        {73.79, 83.89}
    };
    alg::Matrix<double> C = {
        {97.101, 103.107},
        {109.113, 127.131}
    };
    double expected[2][2] = {
        {277911.0130908, 311203.6752936},
        {977091.3716376, 1094161.5164292}
    };

    alg::Matrix<double> M = A * B * C;
    std::pair<std::size_t, std::size_t> d = M.dimension();

    ASSERT_EQ(2, d.first);
    ASSERT_EQ(2, d.second);

    for (std::size_t i = 0; i < d.first; i++) {
        for (std::size_t j = 0; j < d.second; j++) {
            ASSERT_DOUBLE_EQ(expected[i][j], M[i][j]);
        }
    }
}

TEST(Matrix, ScalarMultiplication) {
    constexpr std::size_t m = 2;
    constexpr std::size_t n = 3;

    alg::Matrix<int> A = {
        {2, 3, 5},
        {7, 11, 13}
    };
    int expected[m][n] = {
        {4, 6, 10},
        {14, 22, 26}
    };

    alg::Matrix<int> B = A * 2;
    alg::Matrix<int> C = 2 * A;

    for (std::size_t i = 0; i < m; i++) {
        for (std::size_t j = 0; j < n; j++) {
            ASSERT_EQ(expected[i][j], B[i][j]);
            ASSERT_EQ(expected[i][j], C[i][j]);
        }
    }
}

TEST(Matrix, InvalidArgumentConstructor) {
    ASSERT_THROW(alg::Matrix<int> M(0, 0), std::invalid_argument);
    ASSERT_THROW(alg::Matrix<int> M(0, 1), std::invalid_argument);
    ASSERT_THROW(alg::Matrix<int> M(1, 0), std::invalid_argument);
    ASSERT_NO_THROW(alg::Matrix<int> M(1, 1));
}

TEST(Matrix, InvalidArgumentInitializerList) {
    ASSERT_THROW(alg::Matrix<int> M = {{}}, std::invalid_argument);

    try {
        alg::Matrix<int> M = {
            {2},
            {3, 5}
        };
        FAIL();
    } catch (const std::invalid_argument& e) {}
}

TEST(Matrix, InvalidArgumentCopyAssignment) {
    alg::Matrix<int> A(2, 3);
    alg::Matrix<int> B(5, 3);
    alg::Matrix<int> C(2, 7);
    alg::Matrix<int> D(2, 3);

    ASSERT_THROW(A = B, std::invalid_argument);
    ASSERT_THROW(A = C, std::invalid_argument);
    ASSERT_THROW(B = C, std::invalid_argument);
    ASSERT_NO_THROW(A = D);
}

TEST(Matrix, InvalidArgumentAddition) {
    alg::Matrix<int> A(2, 3);
    alg::Matrix<int> B(5, 3);
    alg::Matrix<int> C(2, 7);
    alg::Matrix<int> D(2, 3);

    ASSERT_THROW(A + B, std::invalid_argument);
    ASSERT_THROW(A + C, std::invalid_argument);
    ASSERT_THROW(B + C, std::invalid_argument);
    ASSERT_NO_THROW(A + D);
}

TEST(Matrix, InvalidArgumentSubtraction) {
    alg::Matrix<int> A(2, 3);
    alg::Matrix<int> B(5, 3);
    alg::Matrix<int> C(2, 7);
    alg::Matrix<int> D(2, 3);

    ASSERT_THROW(A - B, std::invalid_argument);
    ASSERT_THROW(A - C, std::invalid_argument);
    ASSERT_THROW(B - C, std::invalid_argument);
    ASSERT_NO_THROW(A - D);
}

TEST(Matrix, InvalidArgumentMultiplication) {
    alg::Matrix<int> A(2, 3);
    alg::Matrix<int> B(3, 2);
    alg::Matrix<int> C(2, 2);

    ASSERT_NO_THROW(A * B);
    ASSERT_NO_THROW(C * A);
    ASSERT_THROW(A * C, std::invalid_argument);
}

}
