#include <stdio.h>

/*
 * so one file can be read and written at one time !
 *
 * */

int main() {
    FILE *fp = fopen("/home/ema/123.txt", "r+b");
    char buf[10];

    if (fp == NULL)
        return -1;
    
    fread(buf, 1, 10, fp); 
    printf("%s\n", buf);

    fwrite(buf, 1, 10, fp);
    printf("%s\n", buf);

    fread(buf, 1, 20, fp);
    printf("%s\n", buf);

    fclose(fp);
    return 0;
}
