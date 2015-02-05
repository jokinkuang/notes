#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    char *str = "";
    if ("" == '\0') 
        printf("\"\" == '\\0' is True\n");
    else
        printf("\"\" == '\\0' is True\n");
    printf("compare an address value with a char value, just lucky they are equal\n");
    printf("\n");



    printf("char *str = \"\";\n");
    if (str == "")
        printf("str == \"\" is True\n");
    else
        printf("str == \"\" is False\n");
    printf("char *str=\"\", so of course str's value equal the address of \"\"\n");
    printf("\n");

    if (str == '\0')
        printf("str == '\\0' is True\n");
    else
        printf("str == '\\0' is False\n");
    printf("str is a pointer, and '\\0' just a value, of course not equal\n");
    printf("\n");

    if (*str == '\0')
        printf("*str == '\\0' is True\n");
    else
        printf("*str == '\\0' is False\n");
    if (str[0] == '\0')
        printf("str[0] == '\\0' is True\n");
    else
        printf("str[0] == '\\0' is False\n");



    if (str == NULL)
        printf("\"\" == NULL is True\n");
    else
        printf("\"\" == NULL is False\n");

    if ('\0' == NULL)
        printf("'\\0' == NULL is True\n");
    else
        printf("'\\0' == NULL is False\n");
    printf("0 always see as '\\0', and this means NULL pointer's address value is 0,\n"
           "we should not always consider this is true\n");

    return 0;
}
