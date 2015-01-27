#ifndef _EIO_CRC_H_
#define _EIO_CRC_H_

static inline uint16_t __crc16_add(unsigned char b, uint16_t acc) {
    acc ^= b;
    acc  = (acc >> 8) | (acc << 8);
    acc ^= (acc & 0xff00) << 4;
    acc ^= (acc >> 8) >> 4;
    acc ^= (acc & 0xff00) >> 5;
    return acc;
}

static inline uint16_t eio_crc16(const unsigned char *data, int len) {
    int acc = 0;
    int i;
    for (i = 0; i < len; i ++) 
        acc = __crc16_add(data[i], acc);
    return acc;
}

#endif
