#include <stdio.h>
#define STRUCT_OFFSET(stru_name, element) (int)&((struct stru_name*)0)->element
struct stru_addr 
{
    int a;
    char b;
    int d;
    char c;
};

int main(void)
{
    struct stru_addr s;
    printf("start addr of s = %x\n", &s.a);
    int offset = STRUCT_OFFSET(stru_addr, c);
    printf("c_addr = %x, offset = %d\n", &s.c, offset);
    printf("start addr of s caculated from c addr: %x\n", (char *)&s.c - offset);

    return 0;
}
