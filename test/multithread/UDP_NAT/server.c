#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUF_LEN (100)

static int __init_udp_server(int port) {
    struct sockaddr_in s_sock;
    int s_fd;

    bzero(&s_sock, sizeof(s_sock));
    s_sock.sin_family = AF_INET;
    s_sock.sin_addr.s_addr = INADDR_ANY;
    s_sock.sin_port = htons(port);

    s_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (s_fd < 0) {
        perror("socket"); 
        return -1;
    }
    if (bind(s_fd, (struct sockaddr *)&s_sock, sizeof(s_sock)) == -1) {
        perror("bind"); 
        return -1;
    }
     
    return s_fd;
}

static int __service(int s_fd) {
    struct sockaddr_in c_sock;
    socklen_t c_sock_len; //= sizeof(c_sock);
    char c_ip[INET_ADDRSTRLEN];
    char buf[BUF_LEN];

    ssize_t len;
    while (1) {
        len = recvfrom(s_fd, buf, BUF_LEN, 0, (struct sockaddr *)&c_sock, &c_sock_len);
        if (len == -1) {
            perror("receive fail");
            return -1;
        }

        printf("INET_ADDRSTRLEN = %d\n", INET_ADDRSTRLEN);
        inet_ntop(AF_INET, &c_sock.sin_addr, c_ip, sizeof(c_ip));
        printf("client IP & Port: [%s : %d]\n", c_ip, ntohs(c_sock.sin_port));
        
        len = sendto(s_fd, buf, len, 0, (struct sockaddr *)&c_sock, c_sock_len);
        if (len < 0) {
            perror("send fail"); 
            return -1;
        }
    }
}


int main(int argc, char **argv) {
    if (argc < 2) {
        printf("usage: %s <port>\n", argv[0]); 
        exit(1);
    }

    int port;
    port = atoi(argv[1]);
    if (port <= 0) {
        printf("<port> should be an availd number\n"); 
        exit(1);
    }

    int s_fd;
    s_fd = __init_udp_server(port);
    if (s_fd < 0) {
        printf("init server fail\n");
        exit(1);
    }

    printf("server running ...\n");

    if (__service(s_fd) < 0)
        exit(1);

    return 0;
}
