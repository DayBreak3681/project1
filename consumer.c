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
    printf("beginning of consumer funtion");
    int fd;
    struct shmbuf *shmp;
    fd = shm_open("/xyzabc",O_RDWR, 0600);
    if(fd == -1){
        printf("Error opening shared memory\n");
    }
    ftruncate(fd, sizeof(struct shmbuf));
    shmp = mmap(NULL, sizeof(*shmp), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    while (1)
    {
        printf("In the while loop!\n");
        int y;
        sem_wait(&shmp->semEmpty);
        printf("called sem_wait\n");
        y = shmp->buffer[count % 10];
        printf("decrementing the count\n");
        count++;
        sem_post(&shmp->semFull);
        // Consume
        printf("consuming\n");
        ++count;
        printf("Got %d\n", y);
        sleep(1);
    }
}

int main(int argc, char *argv[])
{
    printf("In main\n");
    srand(time(NULL));
    pthread_t th[THREAD_NUM];
    int i;

    for (i = 0; i < THREAD_NUM; i++)
    {
        printf("in first for loop");
        if (pthread_create(&th[i], NULL, &consumer, NULL) != 0)
        {
            printf("In first if statement\n");
            perror("Failed to create thread");
        }
    }
    for (i = 0; i < THREAD_NUM; i++)
    {
        printf("in second for loop\n");
        if (pthread_join(th[i], NULL) != 0)
        {
            printf("in second if statement\n");
            perror("Failed to join thread");
        }
    }
    //sem_destroy(&shmp->semEmpty);
    //sem_destroy(&shmp->semFull);
    shm_unlink("/xyzabc");
    exit(EXIT_SUCCESS);
    printf("finished\n");
    return 0;
}