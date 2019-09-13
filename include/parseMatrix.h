/**
 * readMatrix.h
 *
 * Written by Nicholas Cannon (22241579)
 */
#ifndef PARSE_MATRIX_HEADER
#define PARSE_MATRIX_HEADER

/* Coordinate Format struct */
typedef struct {
    int rows;
    int cols;
    int NZ[];  // non zero elements
} COO_INT;
typedef struct {
    int rows;
    int cols;
    float NZ[];  // non zero elements
} COO_FLOAT;

/* Compressed Format struct (used for both compressed col and row) */
typedef struct {
    int rows;
    int cols;
    int NNZ[];  // non-zero elments
    int IA[];
    int JA[];
} CS_INT;
typedef struct {
    int rows;
    int cols;
    float NNZ[];  // non-zero elments
    int IA[];
    int JA[];
} CS_FLOAT;

#endif
