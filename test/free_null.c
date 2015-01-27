#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p = NULL;
    free(p);
    printf("It won't be wrong to free(NULL);\n");
    return 0;
}
