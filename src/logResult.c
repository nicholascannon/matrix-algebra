/**
 * logResult.c - Logs matrx results to file
 *
 * Written by Nicholas Cannon (22241579)
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "logResult.h"
#include "parseMatrix.h"

/**
 * Stores logfile name in filename in the format of:
 *      <STUDENT_NUM>_<DDMMYYYY>_<HHMM>_<OP>.out
 * len = 8 + 1 + 8 + 1 + 4 + 1 + 2 + 4 = 29
 *
 * file name will always be length of of 29!
 */
static void getFileName(char* op, char* filename) {
    time_t timer;
    time(&timer);
    struct tm* tm_info;
    tm_info = localtime(&timer);
    char timestr[14];
    strftime(timestr, 13, "%d%m%Y_%H%M", tm_info);

    snprintf(filename, LOG_FILE_LEN * sizeof(char), "%s_%s_%s.out", STUDENT_NUM,
             timestr, op);
}

/**
 * Logs a COO matrix. 'file2' should be set to NULL if not required. Returns
 * non-zero on failure.
 */
int logCOO(char* op, char* file1, char* file2, int threadNum, COO* mat,
           float loadTime, float opTime) {
    char* filename = malloc(sizeof(char) * LOG_FILE_LEN);
    getFileName(op, filename);

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
