#include "libs/data_structures/matrix/matrix.h"
#include <stdlib.h>

matrix mulMatrices(matrix m1, matrix m2) {
    matrix result;
    result.nRows = m1.nRows;
    result.nCols = m2.nCols;
    result.values = (int **)malloc(result.nRows * sizeof(int *));
    for (int i = 0; i < result.nRows; i++) {
        result.values[i] = (int *)malloc(result.nCols * sizeof(int));
        for (int j = 0; j < result.nCols; j++) {
            result.values[i][j] = 0;
            for (int k = 0; k < m1.nCols; k++) {
                result.values[i][j] += m1.values[i][k] * m2.values[k][j];
            }
        }
    }
    return result;
}

void getSquareOfMatrixIfSymmetric(matrix *m) {
    if (isSymmetricMatrix(m)) {
        *m = mulMatrices(*m, *m);
    }
}

int main (){
    matrix m;
    m.nRows = 3;
    m.nCols = 3;
    m.values = (int **)malloc(m.nRows * sizeof(int *));
    for (int i = 0; i < m.nRows; i++) {
        m.values[i] = (int *)malloc(m.nCols * sizeof(int));
    }
    m.values[0][0] = 1; m.values[0][1] = 2; m.values[0][2] = 3;
    m.values[1][0] = 2; m.values[1][1] = 1; m.values[1][2] = 4;
    m.values[2][0] = 3; m.values[2][1] = 4; m.values[2][2] = 1;

    getSquareOfMatrixIfSymmetric(&m);

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