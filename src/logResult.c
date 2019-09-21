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
    strftime(timestr, 13, "%d%m%Y_%H%M", tm_info);

    // Format log filename
    char* filename = malloc(sizeof(char) * LOG_FILENAME_LEN);
    snprintf(filename, LOG_FILENAME_LEN * sizeof(char), "%s_%s_%s.out",
             STUDENT_NUM, timestr, op);

    // Construct full path
    strcat(filepath, LOG_PATH);
    strcat(filepath, filename);
    free(filename);
}

/**
 * Logs a COO matrix. 'file2' should be set to NULL if not required. Returns
 * non-zero on failure.
 */
int logCOO(char* op, char* file1, char* file2, int threadNum, COO* mat,
           float loadTime, float opTime) {
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
    if (file2) fprintf(f, "%s\n", file2);
    if (threadNum) fprintf(f, "%d\n", threadNum);
    fprintf(f, "%s\n", mat->type == 0 ? "int" : "float");
    fprintf(f, "%d\n", mat->rows);
    fprintf(f, "%d\n", mat->cols);

    // expand matrix
    fprintf(f, "matrix goes here!\n");

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
           float loadTime, float opTime) {
    return 0;
}
