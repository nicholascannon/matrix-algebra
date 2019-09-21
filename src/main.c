/**
 * CITS3402 Project 1
 *
 * Written by Nicholas Cannon (22241579)
 */
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "logResult.h"
#include "matrixOp.h"
#include "parseMatrix.h"

int main(int argc, char **argv) {
    int lflag = 0;
    int threadNum = 0; // non zero if set by CLA
    int optIndex;
    char *mat1Path, *mat2Path;
    char matOp[3];  // two chars + null byte
    double loadTime = 0.0;
    double opTime = 0.0;
    int status = 0;
    clock_t start, end;

    // quick error check
    if (argc < 2) {
        printf("Invalid comand line args!\n");
        return EXIT_FAILURE;
    }

    // matrix operation always first CLA!
    strncpy(matOp, (argv[1] + 2), 3);

    for (optIndex = 0; optIndex < argc; optIndex++) {
        if (argv[optIndex][0] == '-') {
            switch (argv[optIndex][1]) {
                case 'l':
                    lflag = 1;
                    break;
                case 't':
                    threadNum = atoi(argv[optIndex + 1]);
                    break;
                case 'f':
                    mat1Path = argv[optIndex + 1];
                    if (strcmp(matOp, "ad") || strcmp(matOp, "mm")) {
                        // two matrices provided
                        mat2Path = argv[optIndex + 2];
                    }
            }
        }
    }

    // check if number of threads has been specified
    if (threadNum != 0) {
        omp_set_num_threads(threadNum);
    }

    // TODO: parse matrix files and convert into matrix formats and time process
    // TODO: do matrix op and time process
    // TODO: if lflag then log to file

    if (strcmp(matOp, "sm") == 0) {
        // scalar multiplication
        float scalar = atof(argv[2]);  // argument just after --sm

        // read in matrix
        COO *mat = malloc(sizeof(COO));
        start = clock();
        readCOO(mat1Path, mat);
        end = clock();
        loadTime = (double)(end - start) / CLOCKS_PER_SEC;

        if (status == -1) {
            // failed to open file!
            free(mat);
            printf("Failed to open matrix: %s\n", mat1Path);
            return EXIT_FAILURE;
        }

        // set up answer matrix, basically going to be same size as input
        COO *ans = malloc(sizeof(COO));
        ans->cols = mat->cols;
        ans->rows = mat->rows;
        ans->nzsize = mat->nzsize;
        ans->type = MAT_FLOAT;  // scalar is a float value
        ans->NZ = malloc(ans->nzsize * sizeof(COO_ENTRY_FLOAT));

        // Do opertation
        start = clock();
        scalarMultiplication(mat, ans, scalar);
        end = clock();
        opTime = (double)(end - start) / CLOCKS_PER_SEC;

        if (lflag) {
            // TODO: log answer
        }

        // clean up our allocations
        free(mat);
        free(ans);
    } else if (strcmp(matOp, "tr") == 0) {
        // trace

        // read in matrix
        COO *mat = malloc(sizeof(COO));
        start = clock();
        status = readCOO(mat1Path, mat);
        end = clock();
        loadTime = (double)(end - start) / CLOCKS_PER_SEC;

        if (status == -1) {
            // failed to open file!
            free(mat);
            printf("Failed to open matrix: %s\n", mat1Path);
            return EXIT_FAILURE;
        }

        // trace is only defined for square matrices (row = cols)
        if (mat->rows != mat->cols) {
            printf("Invalid operation: Trace on non square matrix\n");
            free(mat);
            return EXIT_FAILURE;
        }

        // Do opertation
        if (mat->type == MAT_FLOAT) {
            float ans;

            start = clock();
            trace_FLOAT(mat, &ans);
            end = clock();
            opTime = (double)(end - start) / CLOCKS_PER_SEC;

            printf("TIME = %f\n", opTime);
            printf("%f\n", ans);
        } else {
            int ans;

            start = clock();
            trace_INT(mat, &ans);
            end = clock();
            opTime = (double)(end - start) / CLOCKS_PER_SEC;

            printf("TIME = %f\n", opTime);
            printf("%d\n", ans);
        }

        if (lflag) {
            // TODO: log answer
        }

        free(mat);
    } else if (strcmp(matOp, "ad") == 0) {
        // matrix addition
        int status2;

        // read in both matrices
        COO *mat1 = (COO *)malloc(sizeof(COO));
        COO *mat2 = (COO *)malloc(sizeof(COO));
        COO *ans = (COO *)malloc(sizeof(COO));

        start = clock();
        status = readCOO(mat1Path, mat1);
        status2 = readCOO(mat2Path, mat2);
        end = clock();
        loadTime = (double)(end - start) / CLOCKS_PER_SEC;

        if (status == -1 || status2 == -1) {
            // failed to open file!
            free(mat1);
            free(mat2);
            free(ans);
            printf("Failed to open matrices: %s and %s\n", mat1Path, mat2Path);
            return EXIT_FAILURE;
        }

        // check equal dimensions
        if (mat1->cols != mat2->cols || mat1->rows != mat2->rows) {
            free(mat1);
            free(mat2);
            free(ans);
            printf("Matrices must be same dimensions for addition!\n");
            return EXIT_FAILURE;
        }

        start = clock();
        matrixAddition(mat1, mat2, ans);
        end = clock();
        opTime = (double)(end - start) / CLOCKS_PER_SEC;

        for (int i = 0; i < ans->nzsize; i++) {
            printf("%d ", ((COO_ENTRY_INT *)ans->NZ[i])->val);
        }

        if (lflag) {
            // TODO: log output
        }

        // free up memory
        free(mat1);
        free(mat2);
        free(ans);
    } else if (strcmp(matOp, "ts") == 0) {
        // transpose
    } else if (strcmp(matOp, "mm") == 0) {
        // matrix multiplication
    } else {
        // invalid matrix op
        printf("Invalid matrix operation!\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
