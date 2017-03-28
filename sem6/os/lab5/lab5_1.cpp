#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <errno.h>

#include <pthread.h>
#include <semaphore.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <time.h>
#include <string.h>

using namespace std;

#define RSEM_NAME "/lab5semR"
#define WSEM_NAME "/lab5semW"
#define MEM_NAME "/lab5mem"
#define PROG_NUM '1'
#define DEF_PERM 0644
#define MEM_PERM PROT_READ | PROT_WRITE

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while(0)

struct ArgCarrier
{
    uint threadNumber;
    bool stopThread;
    sem_t* readSem;
    sem_t* writeSem;
    // For timedwait
    time_t secToWait;
    int* buf;
};

void* thread_func(void* arg)
{
    srand(time(nullptr));
    ArgCarrier* args = reinterpret_cast<ArgCarrier*>(arg);
    while(!args->stopThread)
    {
        int RandomNum = rand();
        printf("RandomNum is %i\n", RandomNum);
        *(args->buf) = RandomNum;
        sem_post(args->writeSem);
        sem_wait(args->readSem);
        sleep(1);
    }
    
    printf("Thread %i was terminated\n", args->threadNumber);
    return nullptr;
}

int main(int argc, char const *argv[])
{
    shm_unlink(MEM_NAME);
    sem_unlink(RSEM_NAME);
    sem_unlink(WSEM_NAME);
    // Init semaphores
    sem_t* rsemy = sem_open(RSEM_NAME, O_CREAT, DEF_PERM, 0);
    if (rsemy == SEM_FAILED) handle_error("Unable to open read semaphore");
    sem_t* wsemy = sem_open(WSEM_NAME, O_CREAT, DEF_PERM, 0);
    if (wsemy == SEM_FAILED) handle_error("Unable to open write semaphore");

    // Init shared memory
    int mem = shm_open(MEM_NAME, O_CREAT | O_RDWR, DEF_PERM);
    printf("Mem dis %i\n", mem);
    if (mem == -1) handle_error("Unable to open shared memory");
    if (ftruncate(mem, sizeof(int)) != 0) handle_error("Unable to truncate memory");

    // Init buffer    
    int* buf =  reinterpret_cast<int*>(mmap(nullptr, sizeof(int), MEM_PERM, MAP_SHARED, mem, 0));
    if (buf == MAP_FAILED) handle_error("Unable to map memory");

    // Init argcarrier
    ArgCarrier t1 = {1, false, rsemy, wsemy, 10, buf};

    // Init threads
    pthread_t thread;
    if (pthread_create(&thread, nullptr, thread_func, &t1) != 0)
        handle_error("Unable to create thread");

    // It's time to stop
    getchar();
    t1.stopThread = true;

    // Cleanup
    if (pthread_join(thread, nullptr) != 0) handle_error("Unable to join thread");
    if (sem_close(rsemy) != 0) handle_error("Unable to close read semaphore");
    if (sem_close(wsemy) != 0) handle_error("Unable to close write semaphore");
    if (sem_unlink(RSEM_NAME) != 0) handle_error("Unable to unlink read semaphore");
    if (sem_unlink(WSEM_NAME) != 0) handle_error("Unable to unlink write semaphore");
    if (munmap(buf, sizeof(int)) != 0) handle_error("Unable to unmap memory");
    if (close(mem) != 0) handle_error("Unable to close memory");
    if (shm_unlink(MEM_NAME) != 0) handle_error("Unable to unlink memory");

    return EXIT_SUCCESS;
}
