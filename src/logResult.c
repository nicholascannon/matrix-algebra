/**
 * logResult.c - Logs matrx results to file
 *
 * Written by Nicholas Cannon (22241579)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "logResult.h"
#include "parseMatrix.h"

/**
 * Stores logfile name in filename in the format of:
 *      LOG_PATH + <STUDENT_NUM>_<DDMMYYYY>_<HHMM>_<OP>.out
 */
static void getFilePath(char* op, char* filepath) {
    // Format time string
    time_t timer;
    time(&timer);
    struct tm* tm_info;
    tm_info = localtime(&timer);
    char timestr[14];
    strftime(timestr, 14, "%d%m%Y_%H%M", tm_info);

    // Format log filename
    char* filename = malloc(sizeof(char) * LOG_FILENAME_LEN);
    snprintf(filename, LOG_FILENAME_LEN * sizeof(char), "%s_%s_%s.out",
             STUDENT_NUM, timestr, op);

    // Construct full path
    strcpy(filepath, LOG_PATH);
    strncat(filepath, filename, strlen(filename));
    free(filename);
}

/**
 * Logs a single float value. Returns non-zero on failure.
 */
int logFloat(char* op, char* file1, int threadNum, float number, float loadTime,
             float opTime) {
    FILE* f;

    // create file path
    char* fullPath = malloc(strlen(LOG_PATH) + LOG_FILENAME_LEN);
    getFilePath(op, fullPath);

    // create new log file
    f = fopen(fullPath, "w");
    if (f == NULL) return -1;

    // write header info
    fprintf(f, "%s\n", op);
    fprintf(f, "%s\n", file1);
    if (threadNum) fprintf(f, "%d\n", threadNum);
    fprintf(f, "%f\n", number);
    // log timing details
    fprintf(f, "%f\n", loadTime);
    fprintf(f, "%f\n", opTime);

    // clean up and exit
    fclose(f);
    free(fullPath);
    return 0;
}

/**
 * Logs a single int value. Returns non-zero on failure.
 */
int logInt(char* op, char* file1, int threadNum, int number, float loadTime,
           float opTime) {
    FILE* f;

    // create file path
    char* fullPath = malloc(strlen(LOG_PATH) + LOG_FILENAME_LEN);
    getFilePath(op, fullPath);

    // create new log file
    f = fopen(fullPath, "w");
    if (f == NULL) return -1;

    // write header info
    fprintf(f, "%s\n", op);
    fprintf(f, "%s\n", file1);
    if (threadNum) fprintf(f, "%d\n", threadNum);
    fprintf(f, "%d\n", number);
    // log timing details
    fprintf(f, "%f\n", loadTime);
    fprintf(f, "%f\n", opTime);

    // clean up and exit
    fclose(f);
    free(fullPath);
    return 0;
}

/**
 * Logs a COO matrix. 'file2' should be set to NULL if not required. Returns
 * non-zero on failure.
 */
int logCOO(char* op, char* file1, char* file2, int threadNum, COO* mat,
           float loadTime, float opTime, char* scalar) {
    FILE* f;

    // create file path
    char* fullPath = malloc(strlen(LOG_PATH) + LOG_FILENAME_LEN);
    getFilePath(op, fullPath);

    // create new log file
    f = fopen(fullPath, "w");
    if (f == NULL) return -1;

    // write header info
    if (scalar) {
        fprintf(f, "%s %s\n", op, scalar);
    } else {
        fprintf(f, "%s\n", op);
    }
    fprintf(f, "%s\n", file1);
    if (file2) fprintf(f, "%s\n", file2);
    if (threadNum) fprintf(f, "%d\n", threadNum);
    fprintf(f, "%s\n", mat->type == 0 ? "int" : "float");
    fprintf(f, "%d\n", mat->rows);
    fprintf(f, "%d\n", mat->cols);

    // expand matrix
    int i = 0;
    int row = 0;
    int col = 0;
    if (mat->type == MAT_FLOAT) {
        while (i < mat->nzsize) {
            if (mat->NZ[i]->row == row && mat->NZ[i]->col == col) {
                fprintf(f, "%f ", ((COO_ENTRY_FLOAT*)mat->NZ[i])->val);

                i++;  // move to next non-zero element

                // update our indexes to the next position in sparse matrix
                col++;
                if (col == mat->cols) {
                    row++;
                    col = 0;
                }
            } else {
                // calculate the number of zeroes before this non-zero element
                int zCount = mat->cols * (mat->NZ[i]->row - row) +
                             (mat->NZ[i]->col - col);

                for (int j = 0; j < zCount; j++) {
                    fprintf(f, "0.0 ");
                }

                // set indexes to next non zero element
                row = mat->NZ[i]->row;
                col = mat->NZ[i]->col;
            }
        }
    } else {
        while (i < mat->nzsize) {
            if (mat->NZ[i]->row == row && mat->NZ[i]->col == col) {
                fprintf(f, "%d ", ((COO_ENTRY_INT*)mat->NZ[i])->val);

                i++;  // move to next non-zero element

                // update our indexes to the next position in sparse matrix
                col++;
                if (col == mat->cols) {
                    row++;
                    col = 0;
                }
            } else {
                // calculate the number of zeroes before this non-zero element
                int zCount = mat->cols * (mat->NZ[i]->row - row) +
                             (mat->NZ[i]->col - col);

                for (int j = 0; j < zCount; j++) {
                    fprintf(f, "0 ");
                }

                // set indexes to next non zero element
                row = mat->NZ[i]->row;
                col = mat->NZ[i]->col;
            }
        }
    }
    fprintf(f, "\n");
    // log timing details
    fprintf(f, "%f\n", loadTime);
    fprintf(f, "%f\n", opTime);

    // clean up and exit
    fclose(f);
    free(fullPath);
    return 0;
}

/**
 *  Logs a CS matrix. 'file2' should be set to NULL if not required. Returns
 * non-zero on failure
 */
int logCSR(char* op, char* file1, char* file2, int threadNum, CS* mat,
           float loadTime, float opTime, char* scalar) {
    FILE* f;

    // create file path
    char* fullPath = malloc(strlen(LOG_PATH) + LOG_FILENAME_LEN);
    getFilePath(op, fullPath);

    // create new log file
    f = fopen(fullPath, "w");
    if (f == NULL) return -1;

    // write header info
    if (scalar) {
        fprintf(f, "%s %s\n", op, scalar);
    } else {
        fprintf(f, "%s\n", op);
    }
    fprintf(f, "%s\n", file1);
    if (file2) fprintf(f, "%s\n", file2);
    if (threadNum) fprintf(f, "%d\n", threadNum);
    fprintf(f, "%s\n", mat->type == 0 ? "int" : "float");
    fprintf(f, "%d\n", mat->rows);
    fprintf(f, "%d\n", mat->cols);

    // expand matrix
    int i = 0;
    if (mat->type == MAT_FLOAT) {
        for (i = 0; i < mat->rows; i++) {
            // find the number of non-zero elements on ith row
            int nzCount = mat->IA[i + 1] - mat->IA[i];
            if (nzCount == 0) {
                // print mat->col zeroes to log
                for (int j = 0; j < mat->cols; j++) {
                    fprintf(f, "0.0 ");
                }
            } else {
                // we have some non-zero elements on this row
                int col = 0;
                // loop through non-zero elements in this row
                for (int j = mat->IA[i]; j <= mat->IA[i + 1] - 1; j++) {
                    while (col < mat->JA[i]) {
                        fprintf(f, "0.0 ");
                        col++;
                    }
                    fprintf(f, "%f ", ((CS_ENTRY_FLOAT*)mat->NNZ[j])->val);
                    col++;
                }

                // print remaining zeroes to log if required
                while (col < mat->cols) {
                    fprintf(f, "0.0 ");
                    col++;
                }
            }
        }
    } else {
        for (i = 0; i < mat->rows; i++) {
            // find the number of non-zero elements on ith row
            int nzCount = mat->IA[i + 1] - mat->IA[i];
            if (nzCount == 0) {
                // print mat->col zeroes to log
                for (int j = 0; j < mat->cols; j++) {
                    fprintf(f, "0 ");
                }
            } else {
                // we have some non-zero elements on this row
                int col = 0;
                // loop through non-zero elements in this row
                for (int j = mat->IA[i]; j <= mat->IA[i + 1] - 1; j++) {
                    while (col < mat->JA[i]) {
                        fprintf(f, "0 ");
                        col++;
                    }
                    fprintf(f, "%d ", ((CS_ENTRY_INT*)mat->NNZ[j])->val);
                    col++;
                }

                // print remaining zeroes to log if required
                while (col < mat->cols) {
                    fprintf(f, "0 ");
                    col++;
                }
            }
        }
    }
    fprintf(f, "\n");
    // log timing details
    fprintf(f, "%f\n", loadTime);
    fprintf(f, "%f\n", opTime);

    // clean up and exit
    fclose(f);
    free(fullPath);
    return 0;
}
