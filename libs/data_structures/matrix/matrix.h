//
// Created by Admin on 01.04.2024.
//

#ifndef UNTITLED4_MATRIX_H
#define UNTITLED4_MATRIX_H
#include <stdbool.h>
#include <stdio.h>

typedef struct matrix {
    int **values;
    int nRows;
    int nCols;
} matrix;

typedef struct position {
    int rowIndex;
    int colIndex;
} position;

matrix getMemMatrix(int nRows, int nCols);

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols);

void freeMemMatrix(matrix *m);

void freeMemMatrices(matrix *ms, int nMatrices);

void inputMatrix(matrix *m);

void inputMatrices(matrix *ms, int nMatrices);

void swapColumns(matrix m, int j1, int j2);


void outputMatrix(matrix m);

void outputMatrices(matrix *ms, int nMatrices);

void swapRoows(matrix m, int i1, int i2);

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int*, int));

void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int*, int));

bool isSquareMatrix(matrix *m);

bool areTwoMatricesEqual(matrix *m1, matrix *m2);

bool isEMatrix(matrix *m);

bool isSymmetricMatrix(matrix *m);

void transposeSquareMatrix(matrix *m);

void transposeMatrix(matrix *m);

position getMinValuePos(matrix m);

position getMaxValuePos(matrix m);

matrix createMatrixFromArray(const int *a, size_t nRows, size_t nCols);

matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows, size_t nCols);



#endif //UNTITLED4_MATRIX_H
