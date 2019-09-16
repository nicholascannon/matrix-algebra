/**
 * matrixOp.h
 *
 * Written by Nicholas Cannon (22241579)
 */
#include "parseMatrix.h"

#ifndef MATRIX_OP_HEADER
#define MATRIX_OP_HEADER

int scalarMultiplication(COO *mat, COO *ans, float scalar, int numThreads);
int trace_INT(COO *mat, int *ans);
int trace_FLOAT(COO *mat, float *ans);

int matrixAddition(COO *mat1, COO *mat2, COO *ans);

#endif
