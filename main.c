#include <assert.h>
#include <stdio.h>
#include "libs/data_structures/matrix/matrix.h"

void test_functions() {
    // Создаем матрицу для тестирования
    int nRows = 3;
    int nCols = 3;
    matrix m = getMemMatrix(nRows, nCols);

    // Заполняем матрицу значениями
    int counter = 1;
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            m.values[i][j] = counter++;
        }
    }

    // Тестирование функции isSquareMatrix
    assert(isSquareMatrix(&m) == true);

    // Тестирование функции areTwoMatricesEqual
    matrix m1 = getMemMatrix(nRows, nCols);
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            m1.values[i][j] = m.values[i][j];
        }
    }
    assert(areTwoMatricesEqual(&m, &m1) == true);

    // Тестирование функции isEMatrix
    matrix m2 = getMemMatrix(nRows, nCols);
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            m2.values[i][j] = (i == j) ? 1 : 0;
        }
    }
    assert(isEMatrix(&m2) == true);

    // Тестирование функции isSymmetricMatrix
    matrix m3 = getMemMatrix(nRows, nCols);
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            m3.values[i][j] = 1;
        }
    }
    assert(isSymmetricMatrix(&m3) == true);

    // Тестирование функции transposeMatrix
    transposeMatrix(&m);
    assert(m.values[0][0] == 1);
    assert(m.values[0][1] == 4);
    assert(m.values[0][2] == 7);
    assert(m.values[1][0] == 2);
    assert(m.values[1][1] == 5);
    assert(m.values[1][2] == 8);
    assert(m.values[2][0] == 3);
    assert(m.values[2][1] == 6);
    assert(m.values[2][2] == 9);

    // Тестирование функции getMaxValuePos
    position maxPos = getMaxValuePos(m);
    assert(maxPos.rowIndex == 2);
    assert(maxPos.colIndex == 2);

    // Тестирование функции getMinValuePos
    position minPos = getMinValuePos(m);
    assert(minPos.rowIndex == 0);
    assert(minPos.colIndex == 0);

    // Освобождение памяти
    freeMemMatrix(&m);
    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
    freeMemMatrix(&m3);
}

int main() {
    test_functions();
    printf("Все тесты прошли успешно.\n");
    return 0;
}
