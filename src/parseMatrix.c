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
 *  Parses matFile into a COO matrix. Returns non zero on error.
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
    fgets(line, BUF_SIZE, fp);
    mat->rows = atoi(line);
    fgets(line, BUF_SIZE, fp);
    mat->cols = atoi(line);

    // DEBUG ONLY
    // printf("mat type = %d\n", mat->type);
    // printf("rows = %d\n", mat->rows);
    // printf("cols = %d \n", mat->cols);

    // process matrix data
    mat->nzsize = 0;
    while (fgets(line, BUFSIZ, fp) != NULL) {
        token = strtok(line, " ");

        while (token != NULL) {
            if (mat->type == MAT_FLOAT) {
                // convert to float
                float val = atof(token);

                if (val > 0.0) {
                    // we have a non zero!
                    COO_ENTRY_FLOAT *fl =
                        (COO_ENTRY_FLOAT *)malloc(sizeof(COO_ENTRY_FLOAT));
                    fl->val = val;
                    fl->base.row = row;
                    fl->base.col = col;

                    mat->NZ = realloc(
                        mat->NZ, (mat->nzsize + 1) * sizeof(COO_ENTRY_FLOAT));
                    mat->NZ[mat->nzsize] = (COO_ENTRY_BASE *)fl;
                    mat->NZ[mat->nzsize]->col = col;
                    mat->NZ[mat->nzsize]->row = row;

                    mat->nzsize++;
                }
            } else {
                // convert to int
                float val = atoi(token);

                if (val > 0.0) {
                    // we have a non zero!
                    COO_ENTRY_INT *fl =
                        (COO_ENTRY_INT *)malloc(sizeof(COO_ENTRY_INT));
                    fl->val = val;
                    fl->base.row = row;
                    fl->base.col = col;

                    mat->NZ = realloc(
                        mat->NZ, (mat->nzsize + 1) * sizeof(COO_ENTRY_INT));
                    mat->NZ[mat->nzsize] = (COO_ENTRY_BASE *)fl;
                    mat->NZ[mat->nzsize]->col = col;
                    mat->NZ[mat->nzsize]->row = row;

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

    // print our entries FOR DEBUG
    // for (int i = 0; i < mat->nzsize; i++) {
    //     COO_ENTRY_INT *fl = mat->NZ[i];
    //     printf("{ %d, %d, %d }\n", fl->val, fl->base.row, fl->base.col);
    // }

    fclose(fp);
    return 0;
};

/**
 * Parses matFile into CSR matrix. Returns non zero on failure.
 */
int readCSR(char *matFile, CS *mat){};

/**
 * Parses matFile into CSC matrix. Returns non zero on failure.
 */
int readCSC(char *matFile, CS *mat){};
