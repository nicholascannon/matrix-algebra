/**
 * CITS3402 Project 1
 *
 * Written by Nicholas Cannon (22241579)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    COO *mymat = malloc(sizeof(COO));
    readCOO(mat1, mymat);
    free(mymat);

    // if (strcmp(matOp, "sm")) {
    //     // scalar multiplication
    //     float scalar = atof(argv[3]);  // argument just after --sm
    // } else if (strcmp(matOp, "tr")) {
    //     // trace
    // } else if (strcmp(matOp, "ad")) {
    //     // matrix addition
    // } else if (strcmp(matOp, "ts")) {
    //     // transpose
    // } else if (strcmp(matOp, "mm")) {
    //     // matrix multiplication
    // } else {
    //     // invalid matrix op
    //     prinf("Invalid matrix operation!\n");
    //     return EXIT_FAILURE;
    // }

    return EXIT_SUCCESS;
}
