/*
** listener.c -- a datagram sockets "server" demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MYPORT  35622//4950    // the port users will be connecting to
#define DSTPORT 3562//4950    // the port users will be connecting to

#define MAXBUFLEN 100

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in my_addr;    // my address information
    struct sockaddr_in their_addr; // connector's address information
    socklen_t addr_len;
    int numbytes;
    char buf[MAXBUFLEN];

    int port;
    if (argc > 1)
        port = atoi(argv[1]);
    else
        port = MYPORT;
 

    if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    my_addr.sin_family = AF_INET;         // host byte order
    //my_addr.sin_port = htons(port);     // short, network byte order
    my_addr.sin_port = htons(0);     // short, network byte order
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY); // automatically fill with my IP
    memset(&(my_addr.sin_zero), '\0', 8); // zero the rest of the struct

    /*
    if (bind(sockfd, (struct sockaddr *)&my_addr,
        sizeof(struct sockaddr)) == -1) {
        perror("bind failed");
        exit(1);
    }
    */

    // this call is the difference between this program and talker.c:
    int broadcast = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast,
        sizeof(broadcast)) == -1) {
        perror("setsockopt (SO_BROADCAST)");
        exit(1);
    }

    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(DSTPORT);
    their_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);//*((struct in_addr *)he->h_addr);
    memset(&(their_addr.sin_zero), '\0', 8);  // zero the rest of the struct

    addr_len = sizeof(struct sockaddr);
    while (2) {
        char str[] = "status ap ok, EMA-TEST, passwd??";
        int len = sendto(sockfd, str, strlen(str), 0, (struct sockaddr *)&their_addr, addr_len);
       /* 
        if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) < 0) {
            perror("connect failed");
            exit(1);
        }
        
        int len = write(sockfd, str, strlen(str));
        */
 
        printf("len %d response \"%s\"\n", len, str);
        sleep(2);

        //int rfd = accept(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr));
        //len = recv(sockfd, str, strlen(str), 0);
        //len = read(rfd, str, strlen(str));
        /*
        if (len < 0) {
            printf("len %d\n", len);
            exit(1);
        }
        printf("packet contains \"%s\"\n",str);
        */

        if ((numbytes=recvfrom(sockfd, buf, MAXBUFLEN-1 , 0,
                        (struct sockaddr *)&their_addr, &addr_len)) == -1) {
            perror("recvfrom");
            exit(1);
        }

        printf("got packet from %s\n",inet_ntoa(their_addr.sin_addr));
        printf("packet is %d bytes long\n",numbytes);
        buf[numbytes] = '\0';
        printf("packet contains \"%s\"\n",buf);

        //if (strstr(buf, "set ap") != NULL) {
        /*
            char str[] = "set ap ok, EMA-TEST, 123456";
            int len = sendto(sockfd, str, strlen(str), 0, (struct sockaddr *)&their_addr, addr_len);
            printf("len %d response \"%s\"\n", len, str);
            */
        //}
    }
    close(sockfd);

    return 0;
}
