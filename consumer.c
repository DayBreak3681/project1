//Lennice Bolton
// project 1 code.
// 11/7/ 2023

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include "sharedmemory.h"
#include <sys/mman.h>
#include <sys/stat.h> 
#include <fcntl.h>



void *consumer(void *args)
{
    size_t count = 0;
    int fd;
    struct shmbuf *shmp;
    fd = shmget(HELLO,sizeof(struct shmbuf), 0600|IPC_CREAT); //shared memory
    shmp = shmat(fd,NULL,0);
     
    int y;
    for(int i = 0; i < 5; ++i)
    {
        sem_wait(&shmp->semEmpty);
        y = shmp->buffer[count];
        //count++;
        printf("consumed: %d\n", y);
        sem_post(&shmp->semFull);
        // Consume
        ++count;
        sleep(1);
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    pthread_t th[THREAD_NUM];
    int i;

    for (i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_create(&th[i], NULL, &consumer, NULL) != 0)
        {
            perror("Failed to create thread"); //checking to see if we failed to create a thread
        }
    }
    for (i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            perror("Failed to join thread"); //checking to see if we failed to join a thread
        }
    }
    //sem_destroy(&shmp->semEmpty);
    //sem_destroy(&shmp->semFull);
    exit(EXIT_SUCCESS);
    return 0;
}
