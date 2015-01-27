#include <stdio.h>

int main() {
    int my_int = -55;
    double my_double = 10.0;
    int *my_int_ptr;
    double *my_double_ptr;
    my_int_ptr = &my_int;
    my_double_ptr = (double *) my_int_ptr;
    printf("value: %f\n", *my_double_ptr);

    my_int_ptr = (int *)my_double_ptr;
    printf("value: %d\n", *my_int_ptr);

    //print the bytes of Int
    char *my_char_ptr = &my_int;
    //sizeof return long unsigned int
    printf("sizeof char : %ld\n", sizeof(char));
    printf("sizeof int : %ld\n", sizeof(int));
    int i = 0;
    for(i = 0; i < 6; i++)
        printf("%x \n", my_char_ptr[i]);//first: *,last: ++
    return 0;
}
