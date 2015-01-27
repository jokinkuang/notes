#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *ptr;

    ptr = (char *)malloc(10);

    strcpy(ptr, "01234567890");

    return 0;
}
