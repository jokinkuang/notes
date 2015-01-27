#include <stdio.h>

void calc() {
    static i = 0;
    printf("static i = %d\n", i);
}

int main(int argc, char **argv) {
    calc();
    calc();
    calc();
    calc();
    return 0;
}
