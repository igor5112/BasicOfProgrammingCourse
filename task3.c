#include "libs/data_structures/matrix/matrix.h"


int getMin(int *a, int n) {
    int min = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] < min) {
            min = a[i];
        }
    }
    return min;
}


void sortColsByMinElement(matrix m) {
    for (int i = 0; i < m.nCols; i++) {
        int min_index = i;
        for (int j = i+1; j < m.nCols; j++) {
            if (getMin(m.values[j], m.nRows) < getMin(m.values[min_index], m.nRows)) {
                min_index = j;
            }
        }
        if (min_index != i) {
            swapColumns(m, i, min_index);
        }
    }
};
