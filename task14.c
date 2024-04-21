#include <stdio.h>
#include <stdlib.h>
#include "libs/data_structures/matrix/matrix.h"

int countValues(const int *a, int n, int value) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == value) {
            count++;
        }
    }
    return count;
}

int countZeroRows(matrix m) {
    int count = 0;
    for (int i = 0; i < m.nRows; i++) {
        if (countValues(m.values[i], m.nCols, 0) == m.nCols) {
            count++;
        }
    }
    return count;
}

void printMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            printf("%d ", m.values[i][j]);
        }
        printf("\n");
    }
}

void printMatrixWithMaxZeroRows(matrix *ms, int nMatrix) {
    int maxZeroRows = 0;
    for (int i = 0; i < nMatrix; i++) {
        int zeroRows = countZeroRows(ms[i]);
        if (zeroRows > maxZeroRows) {
            maxZeroRows = zeroRows;
        }
    }
    for (int i = 0; i < nMatrix; i++) {
        if (countZeroRows(ms[i]) == maxZeroRows) {
            printMatrix(ms[i]);
            printf("\n");
        }
    }
}

int main() {
    int nMatrix = 5;
    matrix ms[nMatrix];

    for (int i = 0; i < nMatrix; i++) {
        ms[i].nRows = 3;
        ms[i].nCols = 2;
        ms[i].values = (int **)malloc(ms[i].nRows * sizeof(int *));
        for (int j = 0; j < ms[i].nRows; j++) {
            ms[i].values[j] = (int *)malloc(ms[i].nCols * sizeof(int));
        }
    }

    ms[0].values[0][0] = 0; ms[0].values[0][1] = 1;
    ms[0].values[1][0] = 1; ms[0].values[1][1] = 0;
    ms[0].values[2][0] = 0; ms[0].values[2][1] = 0;

    ms[1].values[0][0] = 1; ms[1].values[0][1] = 1;
    ms[1].values[1][0] = 2; ms[1].values[1][1] = 1;
    ms[1].values[2][0] = 1; ms[1].values[2][1] = 1;

    ms[2].values[0][0] = 0; ms[2].values[0][1] = 0;
    ms[2].values[1][0] = 0; ms[2].values[1][1] = 0;
    ms[2].values[2][0] = 4; ms[2].values[2][1] = 7;

    ms[3].values[0][0] = 0; ms[3].values[0][1] = 0;
    ms[3].values[1][0] = 0; ms[3].values[1][1] = 1;
    ms[3].values[2][0] = 0; ms[3].values[2][1] = 0;

    ms[4].values[0][0] = 0; ms[4].values[0][1] = 1;
    ms[4].values[1][0] = 0; ms[4].values[1][1] = 2;
    ms[4].values[2][0] = 0; ms[4].values[2][1] = 3;

    printMatrixWithMaxZeroRows(ms, nMatrix);

    for (int i = 0; i < nMatrix; i++) {
        for (int j = 0; j < ms[i].nRows; j++) {
            free(ms[i].values[j]);
        }
        free(ms[i].values);
    }

    return 0;
}
