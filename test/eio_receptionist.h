/* 
 * File: eio_receptionist.h
 * Author: Terry Lei <freedom@ema-tech.com>
 * Brief: Designed to be used with select(), so that you 
 *        can serve multiple clients in a single thread.
 *
 * Usage: Once the device is available to read (via select()), then call
 *        eio_receptionist_recv_data(); it will read as much data as it can;
 *        once the whole package is read, it will call the hook function  
 *        EIO_ON_PACKAGE_RECV (registered in creator function).
 */
#ifndef _EIO_RECEPTIONIST_H_
#define _EIO_RECEPTIONIST_H_

#include "eio_package.h"

struct eio_receptionist;

typedef int (*EIO_ON_PACKAGE_RECV)(int fd, struct eio_package *pkg, void *user_data);

struct eio_receptionist * eio_receptionist_new(int fd, EIO_ON_PACKAGE_RECV on_pkg_recevied, void *user_data);
void eio_receptionist_release(struct eio_receptionist *);

int  eio_receptionist_get_fd(struct eio_receptionist *);

/* Once a package has been received completely, it will
 * call the hook function EIO_ON_PACKAGE_RECV.
 */
int  eio_receptionist_recv_data(struct eio_receptionist *);

#endif
