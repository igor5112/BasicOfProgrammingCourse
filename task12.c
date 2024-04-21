#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "libs/data_structures/matrix/matrix.h"

position getLeftMin(matrix m) {
    position minPos = {0, 0};
    int minVal = INT_MAX;
    for (int j = 0; j < m.nCols; j++) {
        for (int i = 0; i < m.nRows; i++) {
            if (m.values[i][j] < minVal) {
                minVal = m.values[i][j];
                minPos.rowIndex = i;
                minPos.colIndex = j;
            }
        }
    }
    return minPos;
}

void swapPenultimateRow(matrix m, int n) {
    position minPos = getLeftMin(m);
    for (int i = 0; i < m.nRows; i++) {
        int temp = m.values[n - 2][i];
        m.values[n - 2][i] = m.values[i][minPos.colIndex];
        m.values[i][minPos.colIndex] = temp;
    }
}

int main() {
    matrix m;
    m.nRows = 3;
    m.nCols = 3;
    m.values = (int **)malloc(m.nRows * sizeof(int *));
    for (int i = 0; i < m.nRows; i++) {
        m.values[i] = (int *)malloc(m.nCols * sizeof(int));
    }
    m.values[0][0] = 1; m.values[0][1] = 2; m.values[0][2] = 3;
    m.values[1][0] = 4; m.values[1][1] = 5; m.values[1][2] = 6;
    m.values[2][0] = 7; m.values[2][1] = 8; m.values[2][2] = 1;

    swapPenultimateRow(m, m.nRows);

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            printf("%d ", m.values[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < m.nRows; i++) {
        free(m.values[i]);
    }
    free(m.values);

    return 0;
}
