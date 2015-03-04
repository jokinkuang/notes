#include <stdio.h>

struct book {
    int a;
    int b;
    int c;
};

int main(int argc, char **argv) {
    struct book b[] = {
        {1},
        {1,2},
        {0}
    };
    printf("struct book b[] = { {1},\n {1,2},\n {0} }\n");
    int i;
    for (i = 0; i < sizeof(b)/sizeof(b[0]); i++) {
        printf("book[%d] a=%d b=%d c=%d\n", i, b[i].a, b[i].b, b[i].c);
    }
    printf("Upper array variable is local variable\n");
    printf("But you can see other elements which are not be initialized,\n"
           "are set to Zero by default!\n"
           "This is the characteristic of C Array Initialization!\n");
    return 0;
}
