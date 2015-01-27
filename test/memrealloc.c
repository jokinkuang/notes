#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p = malloc(sizeof(int) * 10);

    p = realloc(p, sizeof(int) * 20);

    free(p);

    return 0;
}
