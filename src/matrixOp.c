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
int scalarMultiplication(COO *mat, COO *ans, float scalar, int numThreads) {
    int i;

    // quick check on inputs
    if (mat->cols != ans->cols || mat->rows != ans->rows ||
        mat->nzsize != ans->nzsize) {
        return -1;
    }

    if (numThreads) {
        omp_set_num_threads(numThreads);
    }

    if (mat->type == MAT_FLOAT) {
#pragma omp parallel for
        for (i = 0; i < mat->nzsize; i++) {
            COO_ENTRY_FLOAT *fl =
                (COO_ENTRY_FLOAT *)malloc(sizeof(COO_ENTRY_FLOAT));
            memcpy(fl, mat->NZ[i], sizeof(COO_ENTRY_FLOAT));

            fl->val = fl->val * scalar;
            ans->NZ[i] = fl;
        }
    } else {
#pragma omp parallel for
        for (i = 0; i < mat->nzsize; i++) {
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

/**
 * Performs a trace on an INTEGER matrix and stores the answer in the ans
 * variable. Trace is the sum of each diagonal element. Note: this function is
 * only defined for square matrices.
 *
 * Returns non-zero on failure.
 */
int trace_INT(COO *mat, int *ans) {
    // basic input sanitization
    if (mat->type != MAT_INT || mat->cols != mat->rows) {
        return -1;
    }

    int trace_sum = 0;
    for (int i = 0; i < mat->nzsize; i++) {
        if (mat->NZ[i]->col == mat->NZ[i]->row) {
            trace_sum += ((COO_ENTRY_INT *)mat->NZ[i])->val;
        }
    }

    *ans = trace_sum;
    return 0;
};

/**
 * Performs a trace on an FLOAT matrix and stores the answer in the ans
 * variable. Trace is the sum of each diagonal element. Note: this function is
 * only defined for square matrices.
 *
 * Returns non-zero on failure.
 */
int trace_FLOAT(COO *mat, float *ans) {
    // basic input sanitization
    if (mat->type != MAT_FLOAT || mat->cols != mat->rows) {
        return -1;
    }

    float trace_sum = 0.0;
    for (int i = 0; i < mat->nzsize; i++) {
        if (mat->NZ[i]->col == mat->NZ[i]->row) {
            trace_sum += ((COO_ENTRY_FLOAT *)mat->NZ[i])->val;
        }
    }

    *ans = trace_sum;
    return 0;
};

int matrixAddition(COO *mat1, COO *mat2, COO *ans){};
