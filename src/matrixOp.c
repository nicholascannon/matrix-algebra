/**
 * matrixOp.c - performs various matrix opertations
 *
 * Written by Nicholas Cannon (22241579)
 */
#include <omp.h>
#include <stdlib.h>
#include <string.h>
#include "parseMatrix.h"

/**
 * Peforms a scalar multiplication on matrix mat and stores the answer in matrix
 * ans. Matrix ans must be the exact same as mat e.g. same rows, cols and
 * nzitems.
 *
 * Returns non zero on failuer.
 */
int scalarMultiplication(COO *mat, COO *ans, float scalar) {
    // quick check on inputs
    if (mat->cols != ans->cols || mat->rows != ans->rows ||
        mat->nzsize != ans->nzsize) {
        return -1;
    }

    if (mat->type == MAT_FLOAT) {
        for (int i = 0; i < mat->nzsize; i++) {
            COO_ENTRY_FLOAT *fl =
                (COO_ENTRY_FLOAT *)malloc(sizeof(COO_ENTRY_FLOAT));
            memcpy(mat->NZ[i], fl, sizeof(COO_ENTRY_FLOAT));

            fl->val = fl->val * scalar;
            ans->NZ[i] = fl;
        }
    } else {
        for (int i = 0; i < mat->nzsize; i++) {
            // Little bit more complicated here as we are storing floats anyway
            COO_ENTRY_FLOAT *fl =
                (COO_ENTRY_FLOAT *)malloc(sizeof(COO_ENTRY_FLOAT));

            fl->base = ((COO_ENTRY_INT *)mat->NZ[i])->base;

            fl->val = ((COO_ENTRY_INT *)mat->NZ[i])->val * scalar;
            ans->NZ[i] = fl;
        }
    }

    return 0;
};
