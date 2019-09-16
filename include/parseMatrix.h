/**
 * readMatrix.h
 *
 * Written by Nicholas Cannon (22241579)
 */
#ifndef PARSE_MATRIX_HEADER
#define PARSE_MATRIX_HEADER

#define MAT_INT 0
#define MAT_FLOAT 1

#define BUF_SIZE 4  // 4 char buf size

/* COORDINATE FORMAT STRUCT */
typedef struct {
    int row;
    int col;
} COO_ENTRY_BASE;

typedef struct {
    COO_ENTRY_BASE base;
    int val;
} COO_ENTRY_INT;

typedef struct {
    COO_ENTRY_BASE base;
    float val;
} COO_ENTRY_FLOAT;

typedef struct {
    int rows;
    int cols;
    int type;  // either MAT_INT or MAT_FLOAT
    int nzsize;
    COO_ENTRY_BASE **NZ;  // non zero elements
} COO;

/* COMPRESSED FORMAT STRUCT */
typedef struct {
    int dummy;
} CS_ENTRY_BASE;

typedef struct {
    CS_ENTRY_BASE base;
    int val;
} CS_ENTRY_INT;

typedef struct {
    CS_ENTRY_BASE base;
    float val;
} CS_ENTRY_FLOAT;

typedef struct {
    int rows;
    int cols;
    int nnzsize;  // size of NNZ
    int type;     // either MAT_INT or MAT_FLOAT
    int *IA;
    int *JA;
    CS_ENTRY_BASE **NNZ;  // non-zero elments
} CS;

/* Function defs */
int readCOO(char *matFile, COO *mat);
int readCSR(char *matFile, CS *mat);  // compressed row
int readCSC(char *matFile, CS *mat);  // compressed col

#endif
