#include <stdio.h>

void test_pointer(int *p) {
     p = NULL; 
}
void test_pointer2(int **p) {
    *p = NULL;
}

int main()
{
    char *my_string;
//just used to format a String into my_string !
//or to combine two String.
    asprintf (&my_string, "Being %d is cool, but being free is best of all.", 4);
    puts (my_string);

    perror("err");

    int a = 10;
    int *p = &a;
    test_pointer(p);
    printf("the address of p ? %p\n", p);
    printf("p is null ? %s\n", p == NULL ? "true" : "false");
    printf("p's value: %d\n", *p);

    test_pointer2(&p);
    printf("the address of p ? %p\n", p);
    printf("p is null? %s\n", p == NULL ? "true" : "flase");
    //printf("p's value: %d\n", *p);

    return 0;
}
