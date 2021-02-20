#include <stdio.h>

void swap (int *a, int *b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}

int GCD(int a, int b) {
    if (a < b)
        swap(&a, &b);

    while (b) {
        a %= b;
        swap(&a, &b);
    }

    return a;
}

int LCM (int a, int b) {
    return a / GCD(a, b) * b;
}

void delete_space (char *str) {
    if (*str == ' ')
        for (char *i = str; *i != '\0'; ++i)
            *i = *(i + 1);
}

void delete_spaces (char *str) {
    if (*str == '\0')
        return;

    if (*str == ' ' && *(str + 1) == ' ') {
        delete_space(str);
        delete_spaces(str);
    }

    delete_spaces(str + 1);
}

int main() {

    printf("The 1st  task:\n");                                      //1st task
    printf("Enter two numbers.\n");
    int a = 0, b = 0, choice = 0;
    scanf("%d%d", &a, &b);
    while (choice != 1 && choice != 2) {
        printf("What would you like to find? Print 1 if GCD or 2 if LCM.\n");
        scanf("%d", &choice);
    }
    if (choice == 1)
        printf("GCD of those numbers is %d.\n", GCD(a,b));
    else
        printf("LCM of those numbers is %d.\n", LCM(a,b));



    printf("5th task:\n");
    char str [128] = {'\0'};
    printf("Print a string.\n");
    gets(str);
    delete_spaces(str);
    printf("%s", str);

    return 0;
}
