#include <stdio.h>

int main() {
    int an_int = 0x66; // 0x00 00 00 66;
    char *first_char = (char *)&an_int;
    int i;
    printf("0x66 in memory is:\n");
    for (i = 0; i < 4; i++)
        printf("%p %02x \n", &first_char[i], first_char[i]);

   if (*first_char == 0x66)
        printf("the low memory is 66 so the cpu is little-endian\n");// little-endian is 0x66 00 00 00
    else
        printf("the low memory is 00 so the cpu is big-endian\n"); //big-endain is 0x00 00 00 66

    //if 0x66 in the memory is 66 00 00 00 then the cpu is little-endian.

    //htonl(0x66) if it is 66 00 00 00 then the network is little-endian too.
    //host to net long so the result is in network-order
    //on the other hand, ntohl(0x03),if it is 03 00 00 00 then the network is little-endian too !
    //so here can be htonl() or ntohl();because if the byte-order changed, it is big-endian.
    //so maybe we can just remember that if 0x66 (00 00 00 66) the order has changed to (低位00 00 00 66高位) then it is big-endian. or it is little-endian. so (低位66 00 00 00高位) is little-endian.

    printf("\n");
    
    int ret = htonl(an_int);        //host-to-network
    first_char = (char *)&ret;
    printf("htonl(0x66) in memory is:\n");
    printf("the value of htonl(0x66) is %d(0x%x)\n", ret, ret);
    for (i = 0; i < 4; i++)
        printf("%p %02x \n", &first_char[i], first_char[i]);

    if (*first_char == 0x66)            // 66 00 00 00 is little-endian
        printf("the low memory is 66 so the network is little-endian\n");
    else
        printf("the low memory is 00 so the network is big-endian\n");

    int num;
    num = -1;
    ret = ntohl(num);
    printf("htonl(-1) = %d ntohl()\n", htonl(-1));

    return 0;
}
