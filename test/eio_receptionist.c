/* 
 * File: eio_recepionist.c
 * Author: Terry Lei <freedom@ema-tech.com>
 * Brief: Implementation of types defined in eio_receptionist.h.
 */
#include "eio_receptionist.h"
#include "eio_protocol.h"
#include "eio_crc.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

struct eio_receptionist {
    int        fd;

    struct eio_header header;
    void *     buffer;    /* to store package data */
    uint32_t   buffer_len;
    int        nread;     /* used only in recv_data() */
    int        (*recv_data)(struct eio_receptionist *); 

    EIO_ON_PACKAGE_RECV on_pkg_recevied;
    void *     user_data; /* for pkg_handler */
};

static int __recv_pkg_header(struct eio_receptionist *);
static int __recv_pkg_data(struct eio_receptionist *);

struct eio_receptionist * eio_receptionist_new(int fd, EIO_ON_PACKAGE_RECV on_pkg_recevied, void *user_data) {
    assert(fd >= 0);
    assert(on_pkg_recevied);
    struct eio_receptionist *receptionist = malloc(sizeof(*receptionist));
    memset(receptionist, 0, sizeof(*receptionist));
    receptionist->fd = fd;
    receptionist->buffer_len = 32;
    receptionist->buffer = malloc(receptionist->buffer_len);
    receptionist->nread = 0;
    receptionist->recv_data = __recv_pkg_header;
    receptionist->on_pkg_recevied = on_pkg_recevied;
    receptionist->user_data = user_data;
    return receptionist;
}

void eio_receptionist_release(struct eio_receptionist *receptionist) {
    assert(receptionist);
    assert(receptionist->fd >= 0);
    assert(receptionist->buffer);
    close(receptionist->fd);
    free(receptionist->buffer);
    free(receptionist);
}

int eio_receptionist_get_fd(struct eio_receptionist *receptionist) {
    return receptionist->fd; 
}

int eio_receptionist_recv_data(struct eio_receptionist *receptionist) {
    assert(receptionist->recv_data);
    return receptionist->recv_data(receptionist);    
}

static int __recv_pkg_header(struct eio_receptionist *receptionist) {
    assert(receptionist->nread >= 0 && receptionist->nread < EIO_HEADER_SIZE); 
    unsigned char *buf = (unsigned char *)&receptionist->header;
    int len = read(receptionist->fd, 
                   buf + receptionist->nread, 
                   EIO_HEADER_SIZE - receptionist->nread);
    if (len < 0) {
        perror("failed to read package header");
        return -1;
    }  
    if (len == 0) // the client has bee closed 
        return -1;

    receptionist->nread += len;
    if (receptionist->nread < EIO_HEADER_SIZE)
        return 0;
    assert(receptionist->nread == EIO_HEADER_SIZE);

    /* now check the header */
    if (! eio_header_check(&receptionist->header)) {
        int i;
        for (i = 1; i < EIO_HEADER_SIZE; i++) {
            if (buf[i] == EIO_ASYNC)
                break;
        }
        memmove(buf, buf+i, EIO_HEADER_SIZE-i);
        receptionist->nread = EIO_HEADER_SIZE-i;
        return 0;
    }

    /* convert to local endian */
    eio_header_to_local_endian(&receptionist->header);

    /* expand buffer if not enough room for package data */
    if (receptionist->buffer_len < receptionist->header.len) {
        size_t new_len;
        if (receptionist->header.len > 10240) 
            new_len = receptionist->header.len;
        else
            new_len = receptionist->header.len * 2;
        free(receptionist->buffer);
        receptionist->buffer = malloc(new_len);
        receptionist->buffer_len = new_len;
    }

    /* change to receiving package data state */
    receptionist->nread = 0;
    receptionist->recv_data = __recv_pkg_data; 

    /* there may still be some data ready to be read,
     * so try to read the package data as much as we can.
     */
    return receptionist->recv_data(receptionist);
}

static int __recv_pkg_data(struct eio_receptionist *receptionist) {
    assert(receptionist->nread >= 0 && receptionist->nread < receptionist->header.len);
    assert(receptionist->buffer_len >= receptionist->header.len);
    int len = read(receptionist->fd, 
                   receptionist->buffer + receptionist->nread,
                   receptionist->header.len - receptionist->nread);
    if (len < 0) {
        perror("failed to receive package data");
        return -1;
    }
    if (len == 0) // client has been closed
        return -1;

    receptionist->nread += len;
    if (receptionist->nread < receptionist->header.len)
        return 0;
    assert(receptionist->nread == receptionist->header.len);

    /* change to receiving package header state */
    receptionist->nread = 0;
    receptionist->recv_data = __recv_pkg_header;

    /* now we got the whole package */
    struct eio_package pkg;
    pkg.cmd = receptionist->header.cmd;
    pkg.len = receptionist->header.len;
    pkg.data = receptionist->buffer;
    return receptionist->on_pkg_recevied(receptionist->fd, &pkg, receptionist->user_data);
}

