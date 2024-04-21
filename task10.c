#include <stdio.h>
#include <stdlib.h>
#include "libs/data_structures/matrix/matrix.h"

int cmp_long_long(const void *pa, const void *pb) {
    long long a = *(long long *)pa;
    long long b = *(long long *)pb;
    return (a > b) - (a < b);
}

int countNUnique(long long *a, int n) {
    qsort(a, n, sizeof(long long), cmp_long_long);
    int count = 1;
    for (int i = 1; i < n; i++) {
        if (a[i] != a[i - 1]) {
            count++;
        }
    }
    return count;
}

int countEqClassesByRowsSum(matrix m) {
    long long rowSums[m.nRows];
    for (int i = 0; i < m.nRows; i++) {
        rowSums[i] = 0;
        for (int j = 0; j < m.nCols; j++) {
            rowSums[i] += m.values[i][j];
        }
    }
    return countNUnique(rowSums, m.nRows);
}

int main() {
    matrix m;
    m.nRows = 6;
    m.nCols = 2;
    m.values = (int **)malloc(m.nRows * sizeof(int *));
    for (int i = 0; i < m.nRows; i++) {
        m.values[i] = (int *)malloc(m.nCols * sizeof(int));
    }
    m.values[0][0] = 7; m.values[0][1] = 1;
    m.values[1][0] = 2; m.values[1][1] = 7;
    m.values[2][0] = 5; m.values[2][1] = 4;
    m.values[3][0] = 4; m.values[3][1] = 3;
    m.values[4][0] = 1; m.values[4][1] = 6;
    m.values[5][0] = 8; m.values[5][1] = 0;

    int count = countEqClassesByRowsSum(m);
    printf("%d", count);

    for (int i = 0; i < m.nRows; i++) {
        free(m.values[i]);
    }
    free(m.values);

    return 0;
}
