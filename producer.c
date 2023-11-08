#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include "sharedmemory.h"
#include <ctype.h>
#include <sys/mman.h>
#include <sys/stat.h> 
#include <fcntl.h>




void *producer(void *args)
{
    size_t count = 0;
    int fd;
    struct shmbuf *shmp;
    fd = shmget(HELLO,sizeof(struct shmbuf), 0600|IPC_CREAT); //shared memory

    shmp = shmat(fd,NULL,0);
    sem_init(&shmp->semEmpty, 1, 5); 
    sem_init(&shmp->semFull, 1, 0);
    int x = 0;
    for (int i = 0; i < 5; ++i)//pushing 5 elements into buffer
    {
    
        
        //sleep(1);

        // Add to the buffer
        sem_wait(&shmp->semFull);
        shmp->buffer[count] = x;
        printf("Produced: %d\n", shmp->buffer[count]);
        count++;
        ++x;
        sem_post(&shmp->semEmpty);
    }

}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    pthread_t th[THREAD_NUM];
    int i;
    for (i = 0; i < THREAD_NUM; ++i)
    {
        if (i >= 0)
        {
            if (pthread_create(&th[i], NULL, &producer, NULL) != 0)
            {
                perror("Failed to create thread"); //checking to see if we failed to create a thread
            }
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
    shm_unlink("/xyzabc");
    exit(EXIT_SUCCESS);
    return 0;
}
