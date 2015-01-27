#include <stdio.h>

void * test() {
    int num = 10;
    int *p = &num;
    return p;
}

int * test6() {
    int num = 10;
    return &num;
}

int * test5(int **p) {
    *p = 10;
}

int main() {
    int *q;
    q = (int *)test();
    printf("q == NULL? %d\n", *q);
    printf("num=%d\n", *q);
    return 0;
}
