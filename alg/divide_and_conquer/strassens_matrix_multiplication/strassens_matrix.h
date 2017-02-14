#ifndef ALG_STRASSENS_MATRIX_H_
#define ALG_STRASSENS_MATRIX_H_

#include "alg/misc/matrix/matrix.h"

namespace alg {

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
Matrix<T> strassens_matrix_multiply(const Matrix<T>& A, const Matrix<T>& B);

}

#include "strassens_matrix.tpp"

#endif
