#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>

struct args {
    int fd;
    struct sockaddr_in addr_in;
};

static pthread_mutex_t _thread_lock;

static void * __service_thread(void *args);

int main(int argc, char **argv) {
    int fd;
    if (argc < 2) {
        printf("Usage: %s <port>\n", argv[0]); 
        exit(0);
    }

    const int port = atoi(argv[1]);
    if (port == 0) {
        printf("<port> is not available\n"); 
        exit(0);
    }

    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
        perror("socket"); 
        exit(2);
    } 
    struct sockaddr_in addr;
    /* we need to fill zero into the addr.sin_zero segment */
    /* we first do like this just make it easy */
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    /* int bind(int sockfd, struct sockaddr *addr, int addrlen); */
    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind"); 
        exit(2);
    }

    if (listen(fd, 20) < 0) {
        perror("listen"); 
        exit(2);
    }

    printf("Server is listening on port [%d]...\n", port);

    pthread_mutex_init(&_thread_lock, NULL);

    while(1){
        struct sockaddr_in c_addr;
        char ip[16] = {0};
        socklen_t addr_len = sizeof(c_addr);
        /* int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen); */ 
        int client_fd = accept(fd, (struct sockaddr *)&c_addr, &addr_len); 
        
        if (inet_ntop(AF_INET, &(c_addr.sin_addr), ip, sizeof(ip)) == NULL) {
            perror("Convert To String IP"); 
            exit(2);
        }
        printf("Client IP&Port: [%s:%d]\n", ip, ntohs(c_addr.sin_port));
        if (client_fd < 0) {
            perror("accept");
            exit(2);
        }
        printf("client [%d] connected...\n", client_fd);
        pthread_t tid;
        /*
        int pthread_create(pthread_t *restrict thread,
                    const pthread_attr_t *restrict attr,
                        void *(*start_routine)(void*), void *restrict arg); */
        int ret = pthread_create(&tid, NULL, __service_thread, &client_fd);
        if (ret != 0) {
            printf("create thread fail, %s\n", strerror(ret)); 
            exit(2);
        }
        
        printf("client [%d] Thread ID %u\n", client_fd, (unsigned int)tid);
        //close(client_fd);
    }

    return 0;
}

/*
 *  pthread_create Need void * (*)(void *) as param
 */
static void * __service_thread(void *args) {
    struct args *client = (struct args *)args
    int fd = client->client_fd;
    int ret = 0;
    int buf_len = 300;
    int i = 0;
    unsigned char buf[buf_len];

    pid_t pid;
    pthread_t  tid;

    pid = getpid();
    tid = pthread_self();

    pthread_mutex_lock(&_thread_lock);
    printf("%s pid %u tid %u (0x%x)\n", "Thread: ", (unsigned int)pid,
                            (unsigned int)tid, (unsigned int)tid);
    pthread_mutex_unlock(&_thread_lock);

    
    while(1) {

        /* flush the buffer */
        bzero(&buf, buf_len);
        
        //read in thread is ok
        ret = read(fd, &buf, buf_len - 1);

        pthread_mutex_lock(&_thread_lock);

        if (ret < 0) {
            perror("read"); 
            printf("client [%d] error\n", fd);
            pthread_mutex_unlock(&_thread_lock);
            break; 
        }

        if (ret == 0) {
            printf("client [%d] close\n", fd);
            pthread_mutex_unlock(&_thread_lock);
            break;
        }

        printf("client [%d] say:\n", fd);
        for (i = 0; i < ret; i++) {
            printf("%x ", buf[i]); 
        }
        printf("\n");
        pthread_mutex_unlock(&_thread_lock);
        break;
    } 
    
    /*
     * though here close the client_fd 
     * the main thread will know a definite delay !
     * because the print out is 
     * [4] //first time it is 4
     * [5] //thread has close fd = 4 but the main thread still don't know that and use fd = 5.
     * [4] //this time the main thread know that fd = 4 has been closed and use fd = 4.
     * [5] //again ! 
     * I don't know why.
     * if the close(client_fd) is in main thread, it won't be like that. fd will alway be 4 !
     * Why close(client_fd) in thread will make it so strange !
     *
     */
    printf("close fd\n");
    
    printf("%d\n", close(fd));

    return NULL;
}
