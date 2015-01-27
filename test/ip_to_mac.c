#include <stdio.h>
#include <assert.h>

#define IP_STR_LEN     18
#define MAC_STR_LEN    18
#define MAC_BIT_LEN    6
#define LITTLE_ENDIAN  0
#define BIG_ENDIAN     1

typedef unsigned char  uchar;
typedef unsigned int   uint;

int big_little_endian()
{
    int data = 0x1;
    if (*((char*)&data) == 0x1)
    return LITTLE_ENDIAN;
    return BIG_ENDIAN;
}

/* string to int */
uint ipstr2int(const char * ipstr)
{
    assert(ipstr);
    uint a,b,c,d;
    uint ip = 0;
    sscanf(ipstr,"%u.%u.%u.%u",&a,&b,&c,&d);
    a = (a << 24) ;
    b = (b << 16) ;
    c = (c << 8) ;
    d = (d << 0) ;
    ip = a | b | c | d;
    return ip;
}

/* int to string */
char *int2ipstr(const uint ip, char *ipstr, const uint ip_str_len)
{
    assert(ipstr);
    if (big_little_endian() == LITTLE_ENDIAN)
    sprintf(ipstr,"%u.%u.%u.%u",
        (uchar)*((char*)(&ip)+3),
        (uchar)*((char*)(&ip)+2),
        (uchar)*((char*)(&ip)+1),
        (uchar)*((char*)(&ip)+0));
    else
    sprintf(ipstr,"%u.%u.%u.%u",
        (uchar)*((char*)(&ip)+0),
        (uchar)*((char*)(&ip)+1),
        (uchar)*((char*)(&ip)+2),
        (uchar)*((char*)(&ip)+3));

    return ipstr;
}

/* char array to string */
char *mac2str(const unsigned char *mac,char *mac_str,const uint mac_str_len)
{
    assert(mac_str);
    sprintf(mac_str,"%02X-%02X-%02X-%02X-%02X-%02X",
        mac[0],mac[1],mac[2],
        mac[3],mac[4],mac[5]);
}

int main()
{
    char  ip_str[IP_STR_LEN] = {0};
    char  mac_str[MAC_STR_LEN] = {0};
    unsigned char mac[MAC_BIT_LEN] = {0XEF,0XAD,0XF4,0X4F,0XAA,0X0F};
    const char *ipstr = "10.0.3.193";
    unsigned int ip;
    int2ipstr(167773121,ip_str,IP_STR_LEN);
    mac2str(mac,mac_str,MAC_STR_LEN);
    ip = ipstr2int(ipstr);
    printf("%s\n",ip_str);
    printf("%s\n",mac_str);
    printf("ip:%u\n",ip);
    return 0;
}
