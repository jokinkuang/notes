#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct book_name {
    char *name;
};

struct book {
    struct book_name book_name;
};

int main() {
    struct book *book = calloc(sizeof(char) * sizeof(*book), 1);
    char *name_ = calloc(sizeof(char) * (strlen("abc") + 1), 1);
    strcpy(name_, "abc");
    book->book_name.name = name_;
    book->book_name.name = realloc(book->book_name.name, sizeof(char) * (strlen("abc") + 1));
    strcpy(book->book_name.name, "abc");
    free(book->book_name.name);
    free(book);
    /* We can free a member of an struct which is in other struct */

    /* We can free a NULL pointer */

    /* When we free a pointer pointed to an int or others, 我们不能引用该指针，只能赋值 ! */

    int a = 100;
    int *p = &a;
    printf("Before freed *p = %d\n", *p);

    free(p);

    /* 释放后引用，会使指针p成为野指针，野指针不能被引用！所以下面导致程序崩溃！ */
    printf("After freed *p = %d\n", *p);
    
    return 0;
}
