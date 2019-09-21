/**
 * logResult.h
 *
 * Written by Nicholas Cannon (22241579)
 */
#include "parseMatrix.h"

#ifndef LOG_RESULT_HEADER
#define LOG_RESULT_HEADER

#define STUDENT_NUM "22241579"
#define LOG_FILE_LEN 30

int logCOO(char* op, char* file1, char* file2, int threadNum, COO* mat,
           float loadTime, float opTime);
int logCSR(char* op, char* file1, char* file2, int threadNum, CS* mat,
           float loadTime, float opTime);
#endif
