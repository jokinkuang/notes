#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#include <unistd.h>


#define BYE_OFFICE 12346
#define HELLO_PORT 12345
#define HELLO_GROUP "127.0.0.1"

int main(int argc, char *argv[])
{
    struct sockaddr_in addr;
    struct sockaddr_in addr2;
    int fd;
    int fd2;
    char *message = "Hello, World!";
    char *message2 = "Bye, Office!";

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket");
        exit(1);
    }

    if ((fd2 = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket");
        exit(1);
    }

    /* add this to Enable BroadCast */
    int broadcast = 1;
    // this call is the difference between this program and talker.c:
    if (setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &broadcast,
        sizeof(broadcast)) == -1) {
        perror("setsockopt (SO_BROADCAST)");
        exit(1);
    }
    if (setsockopt(fd2, SOL_SOCKET, SO_BROADCAST, &broadcast,
        sizeof(broadcast)) == -1) {
        perror("setsockopt (SO_BROADCAST)");
        exit(1);
    }



    /* set up destination address */
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);//inet_addr(HELLO_GROUP);
    addr.sin_port=htons(HELLO_PORT);

    memset(&addr2,0,sizeof(addr2));
    addr2.sin_family = AF_INET;
    addr2.sin_addr.s_addr = htonl(INADDR_BROADCAST);//inet_addr(HELLO_GROUP);
    addr2.sin_port=htons(BYE_OFFICE);

    while (1)
    {
        if (sendto(fd, message, strlen(message), 0,(struct sockaddr *) &addr, sizeof(addr)) < 0)
        {
            perror("sendto");
            exit(1);
        }
        sleep(3);
        if (sendto(fd2, message2, strlen(message2), 0,(struct sockaddr *) &addr2, sizeof(addr2)) < 0)
        {
            perror("sendto2");
            exit(1);
        }
        sleep(3);
    }
}
