#include "libs/data_structures/matrix/matrix.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool isUnique(long long *a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (*(a + i) == *(a + j)) {
                return false;
            }
        }
    }
    return true;
}

long long getSum(int *a, int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += *(a + i);
    }
    return sum;
}

void transpose(matrix *m) {
    for (int i = 0; i < m->nRows; i++) {
        for (int j = i; j < m->nCols; j++) {
            int temp = m->values[i][j];
            m->values[i][j] = m->values[j][i];
            m->values[j][i] = temp;
        }
    }
}

void transposeIfMatrixHasNotEqualSumOfRows(matrix *m) {
    long long rowSums[m->nRows];
    for (int i = 0; i < m->nRows; i++) {
        rowSums[i] = getSum(m->values[i], m->nCols);
    }
    if (isUnique(rowSums, m->nRows)) {
        transpose(m);
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
    m.values[2][0] = 7; m.values[2][1] = 8; m.values[2][2] = 9;

    transposeIfMatrixHasNotEqualSumOfRows(&m);

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
