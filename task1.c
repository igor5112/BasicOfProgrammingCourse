#include "libs/data_structures/matrix/matrix.h"

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
