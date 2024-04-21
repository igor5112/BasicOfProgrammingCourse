#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "libs/data_structures/matrix/matrix.h"


int getNorm(matrix m) {
    int maxVal = INT_MIN;
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (abs(m.values[i][j]) > maxVal) {
                maxVal = abs(m.values[i][j]);
            }
        }
    }
    return maxVal;
}

void printMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            printf("%d ", m.values[i][j]);
        }
        printf("\n");
    }
}

void printMatrixWithMinNorm(matrix *ms, int nMatrix) {
    int minNorm = INT_MAX;
    for (int i = 0; i < nMatrix; i++) {
        int norm = getNorm(ms[i]);
        if (norm < minNorm) {
            minNorm = norm;
        }
    }
    for (int i = 0; i < nMatrix; i++) {
        if (getNorm(ms[i]) == minNorm) {
            printMatrix(ms[i]);
            printf("\n");
        }
    }
}

int main() {
    int nMatrix = 3;
    matrix ms[nMatrix];

    for (int i = 0; i < nMatrix; i++) {
        ms[i].nRows = 2;
        ms[i].nCols = 2;
        ms[i].values = (int **)malloc(ms[i].nRows * sizeof(int *));
        for (int j = 0; j < ms[i].nRows; j++) {
            ms[i].values[j] = (int *)malloc(ms[i].nCols * sizeof(int));
        }
    }

    ms[0].values[0][0] = 1; ms[0].values[0][1] = 2;
    ms[0].values[1][0] = 3; ms[0].values[1][1] = 4;

    ms[1].values[0][0] = 5; ms[1].values[0][1] = 6;
    ms[1].values[1][0] = 7; ms[1].values[1][1] = 8;

    ms[2].values[0][0] = 9; ms[2].values[0][1] = 10;
    ms[2].values[1][0] = 11; ms[2].values[1][1] = 12;

    printMatrixWithMinNorm(ms, nMatrix);

    for (int i = 0; i < nMatrix; i++) {
        for (int j = 0; j < ms[i].nRows; j++) {
            free(ms[i].values[j]);
        }
        free(ms[i].values);
    }

    return 0;
}
