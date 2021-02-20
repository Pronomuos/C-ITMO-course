#include <stdio.h>

int main() {

    printf("The 1st task:\n");                                      //The 1st task
    printf("Print a string.\n");
    char str [128] = {'\0'};
    gets(str);
    int count_num = 0, count_upper = 0, count_lower = 0;

    for (char *i = str; *i != '\0'; i++) {
        if (*i >= '0' && *i <= '9')
            ++count_num;
        else if (*i >= 'A' && *i <= 'Z')
            ++count_upper;
        else if (*i >= 'a' && *i <= 'z')
            ++count_lower;
    }

    printf("There are %d numbers, %d upper and %d lower "
           "letters in the string.\n", count_num, count_upper, count_lower);


    printf("The 5th task:\n");                                    //5th task
    double amount, rate;
    unsigned period;

    printf("Enter the initial amount of money: ");
    scanf("%lf", &amount);
    printf("Enter the interest rate (%%): ");
    scanf("%lf", &rate);
    printf("Enter the period of the deposit: ");
    scanf("%u", &period);

    rate /= 100;
    for (int i = 1; i <= period; i++) {
        amount *= 1 + rate / 12;
        printf("The amount on the month %u is %f\n", i, amount);
    }

    return 0;
}
