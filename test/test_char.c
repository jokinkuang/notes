#include <stdio.h>

int main() {
    char c = 0xFF;
    printf("char 0xFF(%ld) == const (0xFF)(%ld) ? %s\n", c, 0xFF, c == 0xFF ? "true" : "false");
    printf("unsigned int 0xFF(%ld) == const (0xFF)(%ld) ? %s\n", ((int)c), 0xFF, (unsigned int)c == 0xFF ? "true" : "false");
    return 0;
}
