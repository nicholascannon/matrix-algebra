/**
 * logResult.h
 *
 * Written by Nicholas Cannon (22241579)
 */
#include "parseMatrix.h"

#ifndef LOG_RESULT_HEADER
#define LOG_RESULT_HEADER

#define STUDENT_NUM "22241579"
#define LOG_FILENAME_LEN 30
#define LOG_PATH "./data/logs/"

int logCOO(char* op, char* file1, char* file2, int threadNum, COO* mat,
           float loadTime, float opTime, char* scalar);
int logCSR(char* op, char* file1, char* file2, int threadNum, CS* mat,
           float loadTime, float opTime);
#endif
