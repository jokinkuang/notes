#include <stdio.h>
#include <string.h>

int main() {
    char s[1];
    strcpy(s, "abcdef");
    printf("%zu\n", strlen(s));
    return 0;
}
/* 用algrind测试，不会出现错误？!，按理应该出现读取了未定义的内存错误才对啊  */
