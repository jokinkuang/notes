#include <stdio.h>

//wrong! 
void * test() {
    int *p;
    int num = 10;
    p = &num;
    return p;
} 

/*
int ** test1() {
    int *p;
    int num = 10;
    p = &num;
    return &p;
}
*/

int test2() {
    int num = 10;
    return num;
} 

//right!
int * test3() {
    static int num = 10;
    return &num;
}

int * test4(int *p) {
    //p is NULL,you can not use *p !
    //if (p == NULL)
    //    return p;
    //*p = 10;
    int num = 10;
    p = &num;
    printf("here\n");
    //return p;
    return &num;
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
    int **p;
    int num;
    q = (int *)test();
    //*q = test2();
    //p = (int **)test1();
    //q = *p;
    //q = malloc(sizeof(int));
    //q = NULL;
    //q = test4(q);
    //q = test6();
    
    printf("q == NULL? %d\n", q==NULL);
    printf("num=%d\n", *q);
    return 0;
}
