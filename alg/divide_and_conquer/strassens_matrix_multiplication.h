#ifndef ALG_DNC_STRASSENS_MATRIX_MULTIPLICATION_H_
#define ALG_DNC_STRASSENS_MATRIX_MULTIPLICATION_H_

#include <cstddef>

#include <stdexcept>
#include <utility>

#include "alg/numeric/matrix.h"

namespace alg {
namespace dnc {

template <class T>
numeric::Matrix<T> strassens_matrix_multiply(const numeric::Matrix<T>& A,
        const numeric::Matrix<T>& B) {

    std::pair<std::size_t, std::size_t> da = A.dimension();
    std::pair<std::size_t, std::size_t> db = B.dimension();

    if ((da.first != da.second) || (db.first != db.second)) {
        throw std::invalid_argument("Require square matrix");
    }

    if (da != db) {
        throw std::invalid_argument("Require same dimensions");
    }

    std::size_t n = da.first;
    std::size_t p = n / 2;

    if (n & (n - 1)) {
        throw std::invalid_argument("Require dimensions to be power of 2");
    }

    numeric::Matrix<T> C(n, n);

    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
    } else {
        numeric::Matrix<T> PA[2][2];
        numeric::Matrix<T> PB[2][2];
        numeric::Matrix<T> PC[2][2];
        numeric::Matrix<T> S[10];
        numeric::Matrix<T> P[7];

        for (std::size_t i = 0; i < 2; ++i) {
            for (std::size_t j = 0; j < 2; ++j) {
                PA[i][j] = A.submatrix(i * p, j * p, p, p);
                PB[i][j] = B.submatrix(i * p, j * p, p, p);
            }
        }

        S[0] = PB[0][1] - PB[1][1];
        S[1] = PA[0][0] + PA[0][1];
        S[2] = PA[1][0] + PA[1][1];
        S[3] = PB[1][0] - PB[0][0];
        S[4] = PA[0][0] + PA[1][1];
        S[5] = PB[0][0] + PB[1][1];
        S[6] = PA[0][1] - PA[1][1];
        S[7] = PB[1][0] + PB[1][1];
        S[8] = PA[0][0] - PA[1][0];
        S[9] = PB[0][0] + PB[0][1];

        P[0] = PA[0][0] * S[0];
        P[1] = S[1] * PB[1][1];
        P[2] = S[2] * PB[0][0];
        P[3] = PA[1][1] * S[3];
        P[4] = S[4] * S[5];
        P[5] = S[6] * S[7];
        P[6] = S[8] * S[9];

        PC[0][0] = P[4] + P[3] - P[1] + P[5];
        PC[0][1] = P[0] + P[1];
        PC[1][0] = P[2] + P[3];
        PC[1][1] = P[4] + P[0] - P[2] - P[6];

        for (std::size_t i = 0; i < 2; ++i) {
            for (std::size_t j = 0; j < 2; ++j) {
                C.copy(PC[i][j], i * p, j * p, 0, 0, p, p);
            }
        }
    }

    return C;
}

}
}

#endif
