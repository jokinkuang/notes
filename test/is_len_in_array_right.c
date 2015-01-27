#include <stdio.h>
#include <string.h>

int main() {
    int len = 10 + strlen("123");
    char *ch = "def";
    len = strlen("abc") + strlen(ch) + 3;
    char arr[len];
    printf("ok len = %d\n", len);
    char arr2[len + 2];
    printf("ok2 strlen(arr2) = %ld", strlen(arr2));
    return 0;
}
