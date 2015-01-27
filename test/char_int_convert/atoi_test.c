#include <stdio.h>
#include <string.h>

char* itoa(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
        *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}

int main() {
    int num;
    printf("atoi(\"abc\") = %d\n", atoi("abc"));
    printf("atoi(\"abc9\") = %d\n", atoi("abc9"));
    printf("atoi(\"9abc\") = %d\n", atoi("9abc"));
    printf("atoi(\"ab9c\") = %d\n", atoi("ab9c"));
    
    char str[15];
    printf("itoa(10) = %s\n", itoa(10, str));
    printf("itoa(1234567890123) = %s(overflow)\n", itoa(1234567890123, str));
    printf("itoa(-1) = %s\n", itoa(-1, str));

    return 0;
}


/*
atoi("abc") = 0
atoi("abc9") = 0
atoi("9abc") = 9
atoi("ab9c") = 0

itoa(10) = 10
itoa(1234567890123) = 1912276171(overflow)
itoa(-1) = -1

 
 * */
