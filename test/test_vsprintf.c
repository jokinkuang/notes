#include <stdio.h>
#include <stdarg.h>
#include <string.h>

char buffer[80];

int vspf(char *fmt, ...)
{
    va_list argptr;
    int cnt;

    va_start(argptr, fmt);
    cnt = vsprintf(buffer, fmt, argptr);
    va_end(argptr);

    return(cnt);
}

int main(void)
{
    int inumber = 30;
    float fnumber = 90.0;
    char string[4] = "abc";

    vspf("%d %f %s", inumber, fnumber, string);
    printf("%s\n", buffer);
    return 0;
} 
