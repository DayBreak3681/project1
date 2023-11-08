#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define HELLO 333
#define THREAD_NUM 1
  /* Maximum size for exchanged string */

/* Define a structure that will be imposed on the shared
 memory object */

struct shmbuf{
    sem_t semEmpty;
    sem_t semFull;
    pthread_mutex_t mutexBuffer;
    char buffer[5];
};
