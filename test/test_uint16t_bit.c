#include <stdio.h>
#include <stdint.h>

int main(int argc, char **argv) {
    uint16_t val = 0x1345;
    printf("val 0x1345 in memroy:\n");
    unsigned char *str = (unsigned char *)&val;
    printf("%X %X\n", str[0], str[1]);
    val = 0x1345 & 0x0001;
    printf("after 0x1345 & 0x0001:\n");
    printf("%X: %X %X\n", val, str[0], str[1]);
    return 0;
}
