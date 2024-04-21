#include "libs/data_structures/matrix/matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


float getDistance(int *a, int n) {
    float sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i] * a[i];
    }
    return sqrt(sum);
}

void insertionSortRowsMatrixByRowCriteriaF(matrix m, float (*criteria)(int *, int)) {
    for (int i = 1; i < m.nRows; i++) {
        int *key = m.values[i];
        float keyCriteria = criteria(key, m.nCols);
        int j = i - 1;
        while (j >= 0 && criteria(m.values[j], m.nCols) > keyCriteria) {
            m.values[j + 1] = m.values[j];
            j = j - 1;
        }
        m.values[j + 1] = key;
    }
}

void sortByDistances(matrix m) {
    insertionSortRowsMatrixByRowCriteriaF(m, getDistance);
}

int main() {
    matrix m;
    m.nRows = 3;
    m.nCols = 3;
    m.values = (int **)malloc(m.nRows * sizeof(int *));
    for (int i = 0; i < m.nRows; i++) {
        m.values[i] = (int *)malloc(m.nCols * sizeof(int));
    }
    // Здесь вы можете заполнить матрицу m
    // ...
    sortByDistances(m);
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

