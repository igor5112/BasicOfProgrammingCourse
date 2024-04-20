#include <stdio.h>

#define ROWS 3
#define COLS 6

int getMin(int *a, int n) {
    int min = *a;
    for (int i = 1; i < n; i++) {
        if (*(a + i) < min) {
            min = *(a + i);
        }
    }
    return min;
}

void sortColsByMinElement(int (*matrix)[COLS]) {
    for (int i = 0; i < COLS - 1; i++) {
        for (int j = 0; j < COLS - i - 1; j++) {
            if (getMin(matrix[j], ROWS) > getMin(matrix[j + 1], ROWS)) {
                for (int k = 0; k < ROWS; k++) {
                    int temp = *(*(matrix + k) + j);
                    *(*(matrix + k) + j) = *(*(matrix + k) + j + 1);
                    *(*(matrix + k) + j + 1) = temp;
                }
            }
        }
    }
}

int main() {
    int matrix[ROWS][COLS] = {
            {3, 5, 2, 4, 3, 3},
            {2, 5, 1, 8, 2, 7},
            {6, 1, 4, 4, 8, 3}
    };

    sortColsByMinElement(matrix);

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", *(*(matrix + i) + j));
        }
        printf("\n");
    }

    return 0;
}
