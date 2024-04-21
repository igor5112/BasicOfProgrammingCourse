#include <stdio.h>
#include <stdlib.h>
#include "libs/data_structures/matrix/matrix.h"

int getNSpecialElement(matrix m) {
    int count = 0;
    for (int j = 0; j < m.nCols; j++) {
        int sum = 0;
        for (int i = 0; i < m.nRows; i++) {
            sum += m.values[i][j];
        }
        for (int i = 0; i < m.nRows; i++) {
            if (m.values[i][j] > sum - m.values[i][j]) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    matrix m;
    m.nRows = 3;
    m.nCols = 4;
    m.values = (int **)malloc(m.nRows * sizeof(int *));
    for (int i = 0; i < m.nRows; i++) {
        m.values[i] = (int *)malloc(m.nCols * sizeof(int));
    }
    m.values[0][0] = 3; m.values[0][1] = 5; m.values[0][2] = 5; m.values[0][3] = 4;
    m.values[1][0] = 2; m.values[1][1] = 3; m.values[1][2] = 6; m.values[1][3] = 7;
    m.values[2][0] = 12; m.values[2][1] = 2; m.values[2][2] = 1; m.values[2][3] = 2;

    int count = getNSpecialElement(m);
    printf("Количество особых элементов: %d\n", count);

    for (int i = 0; i < m.nRows; i++) {
        free(m.values[i]);
    }
    free(m.values);

    return 0;
}
