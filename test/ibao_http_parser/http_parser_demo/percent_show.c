#include <stdio.h>

int main(int argc, char **argv) {

    int ops = 0;
    int i = 0, j = 0;
    int total_ops = 1000000;
    for (j = 0; j < 5; j++) {
        printf("Download[%d]:     ", j + 1);
        ops = 0;
        for (i = 0; i < total_ops; i++) {
            if (ops % 1000 == 0)  {
                printf("\b\b\b\b%3.0f%%", 100 * (float)ops /(float)total_ops);
                fflush(stdout);
                usleep(10000);
            }
            ops += 1;
        }
        printf("\n");
    }
    return 0;
}
