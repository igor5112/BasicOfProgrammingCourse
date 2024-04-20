#include <stdio.h>
#include <assert.h>
#include "libs/data_structures/matrix/matrix.h"

// Функция для получения максимального элемента в массиве
int getMax(int *a, int n) {
    int max = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    return max;
}

// Функция для сортировки строк матрицы по неубыванию наибольших элементов строк
void sortRowsByMaxElement(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        int max_index = i;
        for (int j = i+1; j < m.nRows; j++) {
            if (getMax(m.values[j], m.nCols) < getMax(m.values[max_index], m.nCols)) {
                max_index = j;
            }
        }
        if (max_index != i) {
            swapRows(&m, i, max_index);
        }
    }
}


int main() {

    int nRows = 3, nCols = 3;
    matrix m = getMemMatrix(nRows, nCols);
    int k = 0;
    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            m.values[i][j] = ++k;

    int minRow = 0, maxRow = 0;
    int minVal = m.values[0][0], maxVal = m.values[0][0];
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] < minVal) {
                minVal = m.values[i][j];
                minRow = i;
            }
            if (m.values[i][j] > maxVal) {
                maxVal = m.values[i][j];
                maxRow = i;
            }
        }
    }


    swapRows(&m, minRow, maxRow);




    return 0;
}
