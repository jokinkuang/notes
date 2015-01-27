#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int *q;
    q = malloc(sizeof(int));
    *q = 5;
    printf("%d\n", *q);

    printf("strlen(\"abc\") = %ld\n", strlen("abc"));
    //free(q);

    return 0;
}
