#include <stdio.h>


int main(int argc, char *argv[]) {
    int a[9] = {99, 88, 77, 66, 55, 44, 33, 22, 11};
    for (int el : a)
        printf("%d\n", el);                        // Ввывод значений массива

    int m1[2][2] = {
            {2, 5},
            {2, 2}
    };
    int m2[2][2] = {
            {1, 2},
            {0, 1}
    };
    int result[2][2];
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < 2; ++k) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
    for (auto & line : result) {                // Вывод результирующей матрицы
        printf("\n");
        for (int el : line)
            printf("%d ", el);
    }

    return 0;
}