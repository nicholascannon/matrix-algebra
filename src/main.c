/**
 * CITS3402 Project 1
 *
 * Written by Nicholas Cannon (22241579)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    int lflag = 0;
    int tflag = 0;  // if 1 then threadNum is set
    int threadNum;
    int optIndex;
    char *mat1, *mat2;
    char matOp[3];  // two chars + null byte

    // matrix operation always first CLA!
    strncpy(matOp, (argv[1] + 2), 3);

    for (optIndex = 0; optIndex < argc && argv[optIndex][0] == '-';
         optIndex++) {
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

    // TODO: parse matrix files and convert into matrix formats and time process

    // TODO: switch on matOp and do matrix op and time process

    // TODO: if lflag then log to file

    return EXIT_SUCCESS;
}
