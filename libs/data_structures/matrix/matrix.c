#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
//
// Created by Admin on 01.04.2024.
//

matrix getMemMatrix(int nRows, int nCols){
    int **values = (int **) malloc(sizeof(int) * nRows);

    for (int i = 0; i < nRows; i ++){
        values[i] = (int *) malloc (sizeof (int) * nCols);
    }

    return (matrix){values, nRows, nCols};
};

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols){
    matrix *ms = (matrix*)(malloc(sizeof (int) * nMatrices));

    for (int i = 0; i < nMatrices; i ++){
        ms[i] = getMemMatrix(nRows, nCols);
    }

    return ms;
};

void freeMemMatrix(matrix *m){
    for (int i = 0; i < m->nRows; i ++){
        free(m->values);
    }

    free(m->values);
};

void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        for (int j = 0; j < ms[i].nRows; j++) {
            free(ms[i].values[j]);
        }
        free(ms[i].values);
    }
}
;

void inputMatrix(matrix *m){
    for (int i = 0; i < m->nRows; i ++){
        for (int j = 0; j < m->nCols; j ++){
            scanf("%d", &(m->values[i][j]));
        }
    }
};

void inputMatrices(matrix *ms, int nMatrices){
    for (int i = 0; i < nMatrices; i ++ ){
        inputMatrix(&ms[i]);
    }
};

void outputMatrix(matrix m){
    for (int i = 0; i < m.nRows; i ++){
        for (int j = 0; j < m.nCols; j ++){
            printf("%d", m.values[i][j]);
        }

        printf("\n");
    }
}

void outputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        for (int j = 0; j < ms[i].nRows; j++) {
            for (int k = 0; k < ms[i].nCols; k++) {
                printf("%d ", ms[i].values[j][k]);
            }
            printf("\n");
        }
    }
}

void swapRows(matrix *m, int i1, int i2) {
    assert(i1 >= 0 && i1 < m->nRows && i2 >= 0 && i2 < m->nRows);
    int *temp = m->values[i1];
    m->values[i1] = m->values[i2];
    m->values[i2] = temp;
}

#include <stdio.h>

void swapColumns(matrix m, int j1, int j2) {
    if (j1 < m.nCols && j2 < m.nCols) {
        for (int i = 0; i < m.nRows; i++) {
            int temp = m.values[i][j1];
            m.values[i][j1] = m.values[i][j2];
            m.values[i][j2] = temp;
        }
    } else {
        printf("Column index out of range.\n");
    }
}

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int*, int)) {
    for (int i = 1; i < m.nRows; i++) {
        int j = i;
        while (j > 0 && criteria(m.values[j], m.nCols) < criteria(m.values[j-1], m.nCols)) {
            swapRows(&m.values[j], &m.values[j-1]);
            j--;
        }
    }
};

void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int*, int)) {
    for (int i = 0; i < m.nCols; i++) {
        int min_index = i;
        for (int j = i+1; j < m.nCols; j++) {
            if (criteria(m.values[j], m.nRows) < criteria(m.values[min_index], m.nRows)) {
                min_index = j;
            }
        }
        if (min_index != i) {
            swapColumns(m, i, min_index);
        }
    }
};

bool isSquareMatrix(matrix *m){
    return m->nRows == m->nCols;
}

bool areTwoMatricesEqual(matrix *m1, matrix *m2){
    int flag = 0;
    if (m1->nRows == m2->nRows && m1->nCols == m2->nCols ){
        for (int i = 0; i < m1->nRows; i ++){
            for (int j = 0; j < m1->nCols; j ++){
                if (m1->values[i][j] != m2->values[i][j]){
                    flag = 1;
                    return false;
                    break;
                }
            }
        }if (flag == 0){
            return true;
        }
    }else
        return false;
}

bool isEMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            if (i == j && m->values[i][j] != 1) {
                return false;
            }
            if (i != j && m->values[i][j] != 0) {
                return false;
            }
        }
    }
    return true;
};

bool isSymmetricMatrix(matrix *m) {
    if (m->nRows != m->nCols) {

        return false;
    }
    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < i; j++) {
            if (m->values[i][j] != m->values[j][i]) {

                return false;
            }
        }
    }

    return true;
};

void transposeSquareMatrix(matrix *m) {
    if (isEMatrix(m)) {

        int **temp = malloc(m->nRows * sizeof(int *));
        for (int i = 0; i < m->nRows; i++) {
            temp[i] = malloc(m->nCols * sizeof(int));
        }


        for (int i = 0; i < m->nRows; i++) {
            for (int j = 0; j < m->nCols; j++) {
                temp[i][j] = m->values[j][i];
            }
        }


        for (int i = 0; i < m->nRows; i++) {
            for (int j = 0; j < m->nCols; j++) {
                m->values[i][j] = temp[i][j];
            }
        }

        for (int i = 0; i < m->nRows; i++) {
            free(temp[i]);
        }
        free(temp);
    }
}

void transposeMatrix(matrix *m) {
    int **transposedValues = malloc(m->nRows * sizeof(int *));
    for (int i = 0; i < m->nRows; i++) {
        transposedValues[i] = malloc(m->nCols * sizeof(int));
    }

    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            transposedValues[j][i] = m->values[i][j];
        }
    }


    for (int i = 0; i < m->nRows; i++) {
        free(m->values[i]);
    }
    free(m->values);


    m->values = transposedValues;
}

position getMaxValuePos(matrix m) {
    position maxPos;
    maxPos.rowIndex = 0;
    maxPos.colIndex = 0;
    int maxVal = m.values[0][0];

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] > maxVal) {
                maxVal = m.values[i][j];
                maxPos.rowIndex = i;
                maxPos.colIndex = j;
            }
        }
    }

    return maxPos;
}

position getMinValuePos(matrix m) {
    position minPos;
    minPos.rowIndex = 0;
    minPos.colIndex = 0;
    int minVal = m.values[0][0];

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] < minVal) {
                minVal = m.values[i][j];
                minPos.rowIndex = i;
                minPos.colIndex = j;
            }
        }
    }

    return minPos;
}

matrix createMatrixFromArray(const int *a, size_t nRows, size_t nCols){
    matrix createMatrixFromArray(const int *a,
                                 int nRows, int nCols) {
        matrix m = getMemMatrix(nRows, nCols);
        int k = 0;
        for (int i = 0; i < nRows; i++)
            for (int j = 0; j < nCols; j++)
                m.values[i][j] = a[k++];
        return m;
    }

}


matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows, size_t nCols) {
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);
    int l = 0;
    for (size_t k = 0; k < nMatrices; k++)
        for (size_t i = 0; i < nRows; i++)
            for (size_t j = 0; j < nCols; j++)
                ms[k].values[i][j] = values[l++];
    return ms;
}





