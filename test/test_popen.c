#include <stdio.h>

int main(int argc, char **argv) {
    char buff[256];
    FILE *fp = popen(argv[1], "r");
    if (fp == NULL)
        return -1;
    while (fgets(buff, sizeof(buff), fp) != NULL)
        fputs(buff, stdout);
    pclose(fp);
    return 0;
}
