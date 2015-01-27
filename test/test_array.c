#include <stdio.h>

void sizeof_in_func(int a[]) {
    printf("sizeof %zu\n", sizeof(a)); // JUST GET A POINTER SPACE!
}
void sizeof_in_funcB(int (*a)[]) {  //数组指针
    printf("array sizeof %zu\n", sizeof((*a)));
}
int main() {
    int n;
    n = 10;
    int b[n];
    printf("%zu", sizeof(b));
    scanf("%d", &n);
    int c[n];
    printf("%zu", sizeof(c));
    sizeof_in_func(c);
    sizeof_in_funcB(&c);
    return 0;
}

