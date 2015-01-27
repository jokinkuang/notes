#ifndef _PACKAGE_H_
#define _PACKAGE_H_

enum {
    CMD_CONNECT;
    CMD_HEARTBEAT;
    CMD_TESTING;
    CMD_ESTABLISH;
    CMD_DISCONNECT;
};

struct package {
    uint32_t cmd;
    uint32_t len;
    char     *data;
};







#endif

