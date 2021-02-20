#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    char array1[4];
    char* prt = array1;
    for (int i = 0; i < 4; i++) {
        printf("Array1[%d] = ", i);
        scanf("%c", &prt[i]);
        getc(stdin);
    }

    for (int i = 0; i < 4; i++)
        printf("Array1[%d] = %c\n", i, *(prt + i));


    char* array2 = (char*) malloc(4 * sizeof(char));
    for (int i = 0; i < 4; i++) {
        printf("Array2[%d] = ", i);
        scanf("%c", &array2[i]);
        getc(stdin);
    }
    for (int i = 0; i < 4; i++)
        printf("Array2[%d] = %c\n", i, array2[i]);

    free(array2);
    getc(stdin);
    return 0;
}