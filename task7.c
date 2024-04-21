#include <stdio.h>
#include <stdlib.h>
#include "libs/data_structures/matrix/matrix.h"

int max(int a, int b) {
    return (a > b) ? a : b;
}

long long findSumOfMaxesOfPseudoDiagonal(matrix m) {
    long long sum = 0;
    for (int d = 0; d < m.nCols; d++) {
        int maxVal = m.values[0][d];
        for (int i = 1; i < m.nRows && d - i >= 0; i++) {
            maxVal = max(maxVal, m.values[i][d - i]);
        }
        sum += maxVal;
    }
    for (int d = 1; d < m.nRows; d++) {
        int maxVal = m.values[d][m.nCols - 1];
        for (int i = 1; d + i < m.nRows && m.nCols - 1 - i >= 0; i++) {
            maxVal = max(maxVal, m.values[d + i][m.nCols - 1 - i]);
        }
        sum += maxVal;
    }
    return sum;
}

int main() {
    matrix m;
    m.nRows = 3;
    m.nCols = 4;
    m.values = (int **)malloc(m.nRows * sizeof(int *));
    for (int i = 0; i < m.nRows; i++) {
        m.values[i] = (int *)malloc(m.nCols * sizeof(int));
    }

    long long sum = findSumOfMaxesOfPseudoDiagonal(m);
    printf("%lld", sum);
    for (int i = 0; i < m.nRows; i++) {
        free(m.values[i]);
    }
    free(m.values);
    return 0;
}
