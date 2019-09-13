/**
 * CITS3402 Project 1
 *
 * Written by Nicholas Cannon (22241579)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "logResult.h"
#include "matrixOp.h"
#include "parseMatrix.h"

int main(int argc, char **argv) {
    int lflag = 0;
    int tflag = 0;  // if 1 then threadNum is set
    int threadNum;
    int optIndex;
    char *mat1, *mat2;
    char matOp[3];  // two chars + null byte
    double loadTime = 0.0;
    double opTime = 0.0;
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
                    tflag = 1;
                    threadNum = atoi(argv[optIndex + 1]);
                    break;
                case 'f':
                    mat1 = argv[optIndex + 1];
                    if (strcmp(matOp, "ad") || strcmp(matOp, "mm")) {
                        // two matrices provided
                        mat2 = argv[optIndex + 2];
                    }
            }
        }
    }

    // TODO: parse matrix files and convert into matrix formats and time process
    // TODO: do matrix op and time process
    // TODO: if lflag then log to file

    if (strcmp(matOp, "sm\n")) {
        // scalar multiplication
        float scalar = atof(argv[2]);  // argument just after --sm

        // read in matrix
        COO *mat = malloc(sizeof(COO));
        start = clock();
        readCOO(mat1, mat);
        end = clock();
        loadTime = (double)(end - start) / CLOCKS_PER_SEC;

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

        // print our entries FOR DEBUG
        for (int i = 0; i < ans->nzsize; i++) {
            COO_ENTRY_FLOAT *fl = ans->NZ[i];
            printf("{ %f, %d, %d }\n", fl->val, fl->base.row, fl->base.col);
        }
        printf("%f\n", opTime);

        if (lflag) {
            // TODO: log answer
        }

        // clean up our allocation
        free(mat);
        free(ans);
    } else if (strcmp(matOp, "tr")) {
        // trace
    } else if (strcmp(matOp, "ad")) {
        // matrix addition
    } else if (strcmp(matOp, "ts")) {
        // transpose
    } else if (strcmp(matOp, "mm")) {
        // matrix multiplication
    } else {
        // invalid matrix op
        printf("Invalid matrix operation!\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
