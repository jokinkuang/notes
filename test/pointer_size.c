#include <stdio.h>
#include <stdlib.h>

int main() {
    unsigned int *p = malloc(sizeof(int) * 10);
    int arr[10];
    int *q;
    int *qq1[10]; // pointer array
    int (*qq2)[10]; // array pointer
    if (p == NULL)
        return -1;

    printf("sizeof(p) = %ld\n", sizeof(p));
    printf("sizeof(int *p) = %ld\n", sizeof(*p));   /* we just can get the size of the pointer-type, if we want to know the memory size it points, you should store it by yourself when you do the malloc or realloc! because heap memory managed by programer! */
    printf("sizeof(void *) = %ld\n", sizeof(void *));
    printf("sizeof(arr[10]) = %ld\n", sizeof(arr));
    printf("sizeof(&arr) = %ld\n", sizeof(&arr));
    
    printf("array: sizeof(qq1) = %ld\n", sizeof(qq1));
    //qq = arr;
    printf("value: sizeof(*qq1) = %ld\n", sizeof(*qq1));
    printf("array pointer: sizeof(qq2) = %ld\n", sizeof(qq2));
    printf("sizeof(*qq2) = %ld\n", sizeof(*qq2));
    

    q = (int *)arr;
    printf("sizeof(*q) = %ld\n", sizeof(*q)); /* 4 */
    q = realloc(q, sizeof(int) * 3); /* Run Time Error because *q is in the stack! stack memory can not be malloc, realloc and free ! */
                                     /* So we can not use realloc to change the size of arr[10] */
    printf("sizeof(arr[10]) = %ld\n", sizeof(arr));

    free(p);
    free(q);

    return 0;
}
