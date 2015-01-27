#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

static int __service(char *str_host_ip, char *str_port) {
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));

    int ret = inet_pton(AF_INET, str_host_ip, &addr.sin_addr);
    /*if (ret == 0) {
        printf("<host> is unavailable\n"); 
        return -1;
    } else if (ret < 0) {
        perror("<host>"); 
        return -1;
    }*/

    int port = atoi(str_port);
    if (port <= 0) {
        printf("<port> is unavailable\n"); 
        return -1;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        perror("socket"); 
        return -1;
    }
    
    int len;

    while (1) {
        scanf("enter");
        len = sendto(fd, "abc", strlen("abc") + 1, 0 ,(struct sockaddr *)&addr, sizeof(addr));
        if (len == -1) {
            perror("send"); 
            return -1;
        }
        pause();
    }
}

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: %s <host> <port>\n", argv[0]);
        exit(1);
    }

    if (__service(argv[1], argv[2]) < 0) {
        exit(1); 
    }

    return 0;

} 
