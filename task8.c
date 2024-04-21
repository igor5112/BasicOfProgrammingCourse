#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "libs/data_structures/matrix/matrix.h"


int getMinInArea(matrix m, int startRow, int startCol, int endRow, int endCol) {
    int minVal = INT_MAX;
    for (int i = startRow; i <= endRow; i++) {
        for (int j = startCol; j <= endCol; j++) {
            if (m.values[i][j] < minVal) {
                minVal = m.values[i][j];
            }
        }
    }
    return minVal;
}

int main() {
    matrix m;
    m.nRows = 3;
    m.nCols = 3;
    m.values = (int **) malloc(m.nRows * sizeof(int *));
    for (int i = 0; i < m.nRows; i++) {
        m.values[i] = (int *) malloc(m.nCols * sizeof(int));
    }

    int minVal = getMinInArea(m, 0, 0, 2, 2);

    printf("%d\n", minVal);
    for (int i = 0; i < m.nRows; i++) {
        free(m.values[i]);
    }
    free(m.values);
    return 0;
}
