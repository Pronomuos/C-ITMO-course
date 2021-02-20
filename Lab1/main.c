#include <stdio.h>

int main()
{
    float a = 0;                      /// Считывание вещественного числа
    scanf("%f", &a);
    getc(stdin);

    char b;
    scanf("%c", &b);                  /// Считывание символа

    printf("a = %f\n", a);            /// Вывод вещественного числа
    printf("b = %c", b);              /// Вывод символа

    return 0;
}
