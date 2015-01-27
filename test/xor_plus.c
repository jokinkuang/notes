#include <stdio.h>
#include <stdlib.h>

#define LOWER(c)    (unsigned char)(c | 0x20)

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s <num1> <num2>\n", argv[0]); 
        exit(1);
    }
    /* just need 1 bit */
    unsigned char num1 = atoi(argv[1]);
    unsigned char num2 = atoi(argv[2]);
    if (num1 == 0 || num2 == 0) {
        printf("<num> is unavailable\n"); 
        exit(1);
    }
    
    printf("%c %c\n", num1, num2);
    printf("%d plus %d = %c\n", num1, num2, (unsigned char)(num1 | num2));
    printf("%d plus %d = %c\n", num1, num2, LOWER(num1));
    return 0;
}
