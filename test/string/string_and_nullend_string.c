#include <stdio.h>
#include <string.h>

int main() {
    char dest[300] = "abc\0def";
    char *path1 = "/home/ema/123.txt";
    //char path2[strlen("/home/ema/123.txt")] = "/home/ema/123.txt";
    char path2[17] = "/home/ema/123.txt"; //strlen(path2) == 22 ?!
    char *path3 = path2;

    strcat(dest, path2);
    printf("path1 = %s | path2 =  %s | dest = %s\n", path1, path2, dest);
    printf("strlen(path1) = %d | strlen(path2) = %d | strlen(dest) = %d\n", strlen(path1), strlen(path2), strlen(dest));
    printf("sizeof(path1) = %d | sizeof(path2) = %d | sizeof(dest) = %d\n", sizeof(path1), sizeof(path2), sizeof(dest));

    FILE *fp = fopen(path1, "r+b");
    if (fp == NULL)
        printf("path1 Fail\n");
    else
        printf("path1 Success\n");
    fclose(fp);

    fp = fopen(path2, "r+b");
    if (fp == NULL)
        printf("path2 Fail\n");
    else
        printf("path2 Success\n");
    if (fp != NULL)
        fclose(fp);

    //strcpy,strcat
    strcpy(path2, "abc\0def");
    printf("strcpy(path2, abc\\0def) = %s\n", path2);

    return 0;
}


/*
 strlen(path1) = 17 | strlen(path2) = 22 | strlen(dest) = 25    //strlen计算的是从当前指针到遇到第一个\0的长度。不包含\0自身。
 sizeof(path1) = 8 | sizeof(path2) = 17 | sizeof(dest) = 300    //sizeof计算的是该标识符被分配的空间。是标识符自身对应的栈空间。这个是在编译后就固定的，与程序逻辑无关！
 path1 Success
 path2 Fail
*/
