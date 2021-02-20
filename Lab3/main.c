#include <stdio.h>


int main()
{
    int a;
    printf("1.Print a number in hexadecimal system:\n");
    scanf("%x", &a);
    getc(stdin);

    printf("2.The number in decimal system is %d\n", a);

    printf("3.The number in octal system is %o\n", a);
    printf("The number in octal system, shifted 3 to the right, is %o\n", a >> 3 );

    printf("4.The number in octal system is %o\n", a);
    printf("The number in octal system with not bit operation is %o\n", ~a);

    int b;
    printf("5.Print a number in octal system:\n");
    scanf("%o", &b);
    printf("The second number XOR the first one in octal system = %o\n", b ^ a);

    return 0;
}