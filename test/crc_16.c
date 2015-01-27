#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "crc16.h"
#include "eio_crc.h"
#include "polycrc.h"

int main() {
    unsigned char data[4] = {0x41, 0x42, 0x43, 0};
    unsigned short crc;
    printf("%s\n", data);
    crc = eio_crc16((unsigned char *)data, 3);
    printf("crc is %x\n", crc);
    crc = crc16_ccitt(data, 3);
    printf("crc is %x\n", crc);
    crc = crc16(data, 3);
    printf("crc is %x\n", crc);

    return 0;
}

