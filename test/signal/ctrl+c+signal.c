#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define true 1

void * One(void * no) 
{
        while (true)
        {
        printf("NUAACS1\n");
        sleep(1);
        }
}

void * Two(void * no) 
{
        while (true)
        {
        printf("NUAACS2\n");
        sleep(1);
        }
}

void Stop(int signo) 
{
        printf("oops! stop!!!\n");
        _exit(0); //the differences between _exit(0) and exit(0); 
        /* First: exit(0) is base on _exit(0);
         * Second: exit(0) is the same as return 0 in main.c
         * Third: exit(0) will do some collect things while exiting. such as: 
         *          1, close the unclose files.
         *          2, flush the data-flow into the disk.
         *          and so on
         * */

}

int main()
{
        int res;
        pthread_t A, B;
        signal(SIGINT, Stop); 
        res = pthread_create(&A, NULL, One, NULL);
        res = pthread_create(&B, NULL, Two, NULL);
        res = pthread_join(A, NULL);
        res = pthread_join(B, NULL);

    return 0;
}
