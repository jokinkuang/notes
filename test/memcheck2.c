#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int foo(int x)
{
    if (x < 0) {
        printf("%d ", x);
    }

        return 0;
}

int main(int argc, char *argv[])
{
    int x;
        
    foo(x);

    return 0;
}

