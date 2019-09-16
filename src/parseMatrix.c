/**
 * parseMatrix.c
 *
 * Written by Nicholas Cannon (22241579)
 */
#include "parseMatrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 *  Parses matFile into a COO matrix. Returns non zero on error (-1 if failed to
 *  open file).
 */
int readCOO(char *matFile, COO *mat) {
    FILE *fp;
    char line[BUFSIZ];
    char *token;
    int col = 0;
    int row = 0;

    // open file and check for errors
    fp = fopen(matFile, "r");
    if (fp == NULL) {
        return -1;
    }

    // get data type
    fgets(line, BUFSIZ, fp);
    if (strcmp(line, "int\n") == 0) {
        mat->type = MAT_INT;
    } else if (strcmp(line, "float\n") == 0) {
        mat->type = MAT_FLOAT;
    } else {
        // fail
        fclose(fp);
        return 1;
    }

    // get rows and cols
    fgets(line, BUFSIZ, fp);
    mat->rows = atoi(line);
    fgets(line, BUFSIZ, fp);
    mat->cols = atoi(line);

    mat->NZ = NULL;
    mat->nzsize = 0;

    // process matrix data
    while (fgets(line, BUFSIZ, fp) != NULL) {
        token = strtok(line, " ");

        while (token != NULL) {
            if (mat->type == MAT_FLOAT) {
                // convert to float
                float val = atof(token);

                if (val > 0.0 || val < 0.0) {
                    // we have a non zero!
                    COO_ENTRY_FLOAT *fl =
                        (COO_ENTRY_FLOAT *)malloc(sizeof(COO_ENTRY_FLOAT));
                    fl->val = val;
                    fl->base.row = row;
                    fl->base.col = col;

                    mat->NZ = realloc(
                        mat->NZ, (mat->nzsize + 1) * sizeof(COO_ENTRY_FLOAT));
                    mat->NZ[mat->nzsize] = (COO_ENTRY_BASE *)fl;

                    mat->nzsize++;
                }
            } else {
                // convert to int
                int val = atoi(token);

                if (val > 0 || val < 0) {
                    // we have a non zero!
                    COO_ENTRY_INT *fl =
                        (COO_ENTRY_INT *)malloc(sizeof(COO_ENTRY_INT));
                    fl->val = val;
                    fl->base.row = row;
                    fl->base.col = col;

                    mat->NZ = realloc(
                        mat->NZ, (mat->nzsize + 1) * sizeof(COO_ENTRY_INT));
                    mat->NZ[mat->nzsize] = (COO_ENTRY_BASE *)fl;

                    mat->nzsize++;
                }
            }

            col++;
            if (col == mat->cols) {
                // wrap around
                col = 0;
                row++;
            }
            token = strtok(NULL, " ");
        }
    }

    fclose(fp);
    return 0;
};

/**
 * Parses matFile into CSR matrix. Returns non zero on failure.
 */
int readCSR(char *matFile, CS *mat) {
    FILE *fp;
    char line[BUFSIZ];
    char *token;
    int col = 0;
    int row = 0;
    int nnzCount = 0;

    // open file and check for errors
    fp = fopen(matFile, "r");
    if (fp == NULL) {
        return 1;
    }

    // get data type
    fgets(line, BUFSIZ, fp);
    line[strcspn(line, "\n")] = '\0';  // remove new line for comparison
    if (strcmp(line, "int") == 0) {
        mat->type = MAT_INT;
    } else {
        mat->type = MAT_FLOAT;
    }

    // get rows and cols
    fgets(line, BUFSIZ, fp);
    mat->rows = atoi(line);
    fgets(line, BUFSIZ, fp);
    mat->cols = atoi(line);

    // Initialise IA array
    mat->IA = malloc((mat->rows + 1) * sizeof(int));
    mat->IA[0] = 0;  // convention

    mat->NNZ = NULL;
    mat->JA = NULL;
    mat->nnzsize = 0;

    // process matrix data
    while (fgets(line, BUFSIZ, fp) != NULL) {
        token = strtok(line, " ");

        while (token != NULL) {
            if (mat->type == MAT_FLOAT) {
                // process floats
                float val = atof(token);

                if (val > 0.0 || val < 0.0) {
                    // this is a non zero
                    CS_ENTRY_FLOAT *fl = malloc(sizeof(CS_ENTRY_FLOAT));
                    fl->val = val;

                    mat->NNZ = realloc(
                        mat->NNZ, (mat->nnzsize + 1) * sizeof(CS_ENTRY_FLOAT));
                    mat->JA =
                        realloc(mat->JA, (mat->nnzsize + 1) * sizeof(int));

                    mat->NNZ[mat->nnzsize] = (CS_ENTRY_BASE *)fl;
                    mat->JA[mat->nnzsize] = col;

                    mat->nnzsize++;
                    nnzCount++;
                }
            } else {
                // process ints
                int val = atoi(token);

                if (val > 0 || val < 0) {
                    // this is a non zero
                    CS_ENTRY_INT *fl =
                        (CS_ENTRY_INT *)malloc(sizeof(CS_ENTRY_INT));
                    fl->val = val;

                    mat->NNZ = realloc(
                        mat->NNZ, (mat->nnzsize + 1) * sizeof(CS_ENTRY_INT));
                    mat->JA =
                        realloc(mat->JA, (mat->nnzsize + 1) * sizeof(int));

                    mat->NNZ[mat->nnzsize] = (CS_ENTRY_BASE *)fl;
                    mat->JA[mat->nnzsize] = col;

                    mat->nnzsize++;
                    nnzCount++;
                }
            }

            col++;
            if (col == mat->cols) {
                mat->IA[row + 1] = mat->IA[row] + nnzCount;

                // wrap around
                nnzCount = 0;
                col = 0;
                row++;
            }
            token = strtok(NULL, " ");
        }
    }

    fclose(fp);
    return 0;
};

/**
 * Parses matFile into CSC matrix. Returns non zero on failure.
 */
int readCSC(char *matFile, CS *mat){
    // FILE *fp;
    // char line[BUFSIZ];
    // char *token;
    // int col = 0;
    // int row = 0;
    // int nnzCount = 0;

    // // open file and check for errors
    // fp = fopen(matFile, "r");
    // if (fp == NULL) {
    //     return 1;
    // }

    // // get data type
    // fgets(line, BUFSIZ, fp);
    // line[strcspn(line, "\n")] = '\0';  // remove new line for comparison
    // if (strcmp(line, "int") == 0) {
    //     mat->type = MAT_INT;
    // } else {
    //     mat->type = MAT_FLOAT;
    // }

    // // get rows and cols
    // fgets(line, BUFSIZ, fp);
    // mat->rows = atoi(line);
    // fgets(line, BUFSIZ, fp);
    // mat->cols = atoi(line);

    // // Initialise IA array
    // mat->IA = malloc((mat->rows + 1) * sizeof(int));
    // mat->IA[0] = 0;  // convention

    // mat->NNZ = NULL;
    // mat->JA = NULL;
    // mat->nnzsize = 0;

    // // process matrix data
    // while (fgets(line, BUFSIZ, fp) != NULL) {
    //     token = strtok(line, " ");

    //     while (token != NULL) {
    //         if (mat->type == MAT_FLOAT) {
    //             // process floats
    //             float val = atof(token);

    //             if (val > 0.0 || val < 0.0) {
    //             }
    //         } else {
    //             // process ints
    //             int val = atoi(token);

    //             if (val > 0 || val < 0) {
    //             }
    //         }

    //         token = strtok(NULL, " ");
    //     }
    // }

    // fclose(fp);
    // return 0;
};
