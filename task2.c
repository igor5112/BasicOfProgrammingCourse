#include "libs/data_structures/matrix/matrix.h"


int getMax(int *a, int n) {
    int max = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    return max;
}


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

int main (){
    return 0;
}