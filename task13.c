#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "libs/data_structures/matrix/matrix.h"


bool isNonDescendingSorted(int *a, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (a[i] > a[i + 1]) {
            return false;
        }
    }
    return true;
}

bool hasAllNonDescendingRows(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        if (!isNonDescendingSorted(m.values[i], m.nCols)) {
            return false;
        }
    }
    return true;
}

int countNonDescendingRowsMatrices(matrix *ms, int nMatrix) {
    int count = 0;
    for (int i = 0; i < nMatrix; i++) {
        if (hasAllNonDescendingRows(ms[i])) {
            count++;
        }
    }
    return count;
}

int main() {
    int nMatrix = 4;
    matrix ms[nMatrix];

    for (int i = 0; i < nMatrix; i++) {
        ms[i].nRows = 2;
        ms[i].nCols = 2;
        ms[i].values = (int **)malloc(ms[i].nRows * sizeof(int *));
        for (int j = 0; j < ms[i].nRows; j++) {
            ms[i].values[j] = (int *)malloc(ms[i].nCols * sizeof(int));
        }
    }

    ms[0].values[0][0] = 7; ms[0].values[0][1] = 1;
    ms[0].values[1][0] = 1; ms[0].values[1][1] = 1;

    ms[1].values[0][0] = 1; ms[1].values[0][1] = 6;
    ms[1].values[1][0] = 2; ms[1].values[1][1] = 2;

    ms[2].values[0][0] = 5; ms[2].values[0][1] = 4;
    ms[2].values[1][0] = 2; ms[2].values[1][1] = 3;

    ms[3].values[0][0] = 1; ms[3].values[0][1] = 3;
    ms[3].values[1][0] = 7; ms[3].values[1][1] = 9;

    int count = countNonDescendingRowsMatrices(ms, nMatrix);
    printf("%d", count);

    for (int i = 0; i < nMatrix; i++) {
        for (int j = 0; j < ms[i].nRows; j++) {
            free(ms[i].values[j]);
        }
        free(ms[i].values);
    }

    return 0;
}
