#include "head.h"
/*
struct book {
    int num;
    void *name;
};

*/

struct book boo = {
    10,
    "boo"
};

int g_num2;

int put_out(char *str) {
    printf("%s\n", str);
    return 0;
}
