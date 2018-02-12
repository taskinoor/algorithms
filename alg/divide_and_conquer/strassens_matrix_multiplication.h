#ifndef ALG_DNC_STRASSENS_MATRIX_MULTIPLICATION_H_
#define ALG_DNC_STRASSENS_MATRIX_MULTIPLICATION_H_

#include <cstddef>

#include "alg/numeric/matrix.h"

namespace alg {
namespace dnc {

/**
 * This method works for n x n matrices where n is an exact power of 2. When
 * this constraint is not met missing rows and columns need to be filled with
 * zeros before calling this.
 *
 * Moreover, at each step matrices are partitioned by copying data. Though it
 * won't improve the asymptotic performance, the constant factor can be
 * improved further by partitioning matrices using index calculation.
 */
template <class T>
numeric::Matrix<T> strassens_matrix_multiply(const numeric::Matrix<T>& A,
        const numeric::Matrix<T>& B) {

    std::size_t n = A.dimension().first;
    std::size_t p = n / 2;

    numeric::Matrix<T> C(n, n);

    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
    } else {
        numeric::Matrix<T> PA[2][2];
        numeric::Matrix<T> PB[2][2];
        numeric::Matrix<T> PC[2][2];
        numeric::Matrix<T> S[10];
        numeric::Matrix<T> P[7];

        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
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

        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                C.copy(PC[i][j], i * p, j * p, 0, 0, p, p);
            }
        }
    }

    return C;
}

}
}

#endif
