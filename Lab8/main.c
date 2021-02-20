#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {

    char str1 [255];                                      // The 2nd task
    char str2 [128];
    int n;
    printf("The 2nd task:\n");
    printf("Print a string.\n");
    scanf("%127s", str1);
    printf("Print another string.\n");
    scanf("%127s", str2);
    printf("How many letters to concatenate?\n");
    scanf("%d", &n);
    strncat(str1, str2, n);
    printf ("%s", str1);


    char a [128];                                        // 5th task
    char b [128];
    printf("5th task:\n");
    printf("Print a string.\n");
    scanf("%127s", a);
    strcpy(b, a);
    printf("%s", b);
    getc(stdin);

    char str [128];                                     //8th task
    char ch;
    printf("8th task:\n");
    printf("Print a string.\n");
    scanf("%127s", str);
    getc(stdin);
    printf("Print a character.\n");
    scanf("%c", &ch);
    char *ptr = NULL;
    ptr = strchr(str, ch);
    if (ptr != NULL)
        printf("The chatacter in the position #%ld.\n", ptr - str + 1);
    else
        printf("No such a character in the string.\n");


    printf("11th task:\n");                            //11th task
    char string1[128];
    char string2[128];
    printf("Print a string.\n");
    scanf("%127s", string1);
    printf("Print another string.\n");
    scanf("%127s", string2);
    size_t start = strcspn(string1, string2);
    size_t len = strspn(&string1[start], string2);
    if (len)
        printf("There is a section in the first string that includes letters from the second string.\n"
           "The size of the section - %zu.\n", len);
    else
        printf("There is no section in the first string that includes letters from the second string.\n");


    printf("13th task:\n");                             //13th task
    char s [128];
    char divide[128];
    printf("Print a string.\n");
    gets(s);
    printf("Print another string.\n");
    gets(divide);
    char *p = strtok(s, divide);
    printf("The result: \n");
    while (p != NULL) {
        printf ("%s\n",p);
        p = strtok (NULL, divide);
    }

    return 0;
}