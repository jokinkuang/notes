#include <stdio.h>
#include "head.h"

//extern struct book boo;
//extern int g_num;

int main() {
    static const int n =10;
    int a[n];
    g_num2 = 12;
    put_out("hello\n");
    /* the header hide the struture,we can not access it */
    //put_out(sizeof(struct book));
    //printf("sizeof(long) = %ld\nsizeof(int) = %ld\n", sizeof(long), sizeof(int));
    //printf("boo->num = %d boo->name = %s\n", boo.num, boo.name);
    printf("g_num2 = %d\n", g_num2);
    return 0;
}
