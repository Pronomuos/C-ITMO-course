#include <stdio.h>

int main() {
    int x;
    printf("1.Print a number in the range of [-4, -1]:\n");
    scanf("%d", &x);
    printf("The number is in the range of [-4, -1]: %d\n", (-4 <= x) && (x <= -1));
    printf("2.Print a number in hexadecimal system:\n");
    scanf("%x", &x);
    printf("The bit #15 of the number is %d\n", (x >> 15) % 2);
    for (int i = 0; i < 10; i++)
        x = x / 2;
    printf("The bit #15 of the number is %d\n", x);

    return 0;
}