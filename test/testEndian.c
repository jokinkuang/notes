#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main()
{
        int16_t x = 1;  //0x 00 01
        if(*(char*)&x == 1) //01 00 is little-endian
                printf("little endian\n");
        else
                printf("big endian\n");

        int16_t y = ntohs(x); //network-to-host  //0x00 01 -> host
        char *by = (char *)&y;
        printf("ntohs(1) = %d(0x%x)\n", ntohs(x), ntohs(x));
        int i = 0;
        for(i = 0; i < 2; i++)
            printf("%p = %02x\n", &by[i], by[i]);

        if(*(char*)&y == 1)   //01 00 is little-endian
                printf("net little endian\n");
        else                    //00 01 is big-endia
                printf("net big endian\n");
        return 0;
}

