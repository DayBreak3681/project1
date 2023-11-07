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
    fd = shm_open("/xyzabc", O_CREAT | O_EXCL | O_RDWR, 0600);
    ftruncate(fd, sizeof(struct shmbuf));
    shmp = mmap(NULL, sizeof(*shmp), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    sem_init(&shmp->semEmpty, 1, 0);
    sem_init(&shmp->semFull, 1, 2);
    while (1)
    {
        // Produce
        int x = rand() % 100;
        //sleep(1);

        // Add to the buffer
        sem_wait(&shmp->semFull);
        shmp->buffer[count] = x;
        count++;
        sem_post(&shmp->semEmpty);
    }

}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    pthread_t th[THREAD_NUM];
    int i;
    for (i = 0; i < THREAD_NUM; i++)
    {
        if (i > 0)
        {
            if (pthread_create(&th[i], NULL, &producer, NULL) != 0)
            {
                perror("Failed to create thread");
            }
        }
    }
    for (i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            perror("Failed to join thread");
        }
    }
    //sem_destroy(&shmp->semEmpty);
    //sem_destroy(&shmp->semFull);
    shm_unlink("/xyzabc");
    exit(EXIT_SUCCESS);
    return 0;
}
