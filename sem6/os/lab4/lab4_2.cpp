#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <errno.h>

#include <pthread.h>
#include <semaphore.h>

#include <fcntl.h>
#include <sys/stat.h>

using namespace std;

#define SEM_NAME "/lab4"
#define PROG_NUM '2'
#define OUTPUT_FILE "./out"

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while(0)

struct ArgCarrier
{
    uint threadNumber;
    bool stopThread;
    sem_t* semp;
    // For timedwait
    time_t secToWait;
    int file;
};

void* thread_func(void* arg)
{
    ArgCarrier* args = reinterpret_cast<ArgCarrier*>(arg);
    while(!args->stopThread)
    {
        // wait section
        if (sem_wait(args->semp) != 0) handle_error("Unable to wait");
        // trywait section
        // if (sem_trywait(args->semp) != 0) {
        //     if (errno == EAGAIN) continue;
        //     else handle_error("Unable to trywait");
        // }

        // timedwait section
        // timespec ts;
        // if (clock_gettime(CLOCK_REALTIME, &ts) != 0) handle_error("Unable to get time");
        // ts.tv_sec += args->secToWait;
        // if (sem_timedwait(args->semp, &ts) != 0)
        // {
        //     if (errno == ETIMEDOUT)
        //     {
        //         printf("Thread %i timed out\n", args->threadNumber);
        //         break;
        //     } else handle_error("Unable to wait");
        // }

        // Basic operation
        char buf = PROG_NUM;
        for (int i = 0; i < 5; ++i)
            if (write(args->file, &buf, 1) == -1) handle_error("Unable to write to file");
        sem_post(args->semp);
        sleep(1);
    }
    
    printf("Thread %i was terminated\n", args->threadNumber);
    return nullptr;
}

int main(int argc, char const *argv[])
{
    // Init semaphore
    sem_t* semy = sem_open(SEM_NAME, O_CREAT, 0644, 1);
    if (semy == SEM_FAILED) handle_error("Unable to open semaphore");

    // Init filedes
    int file = open(OUTPUT_FILE, O_CREAT | O_APPEND | O_WRONLY | O_NONBLOCK, 0644);
    if (file == -1) handle_error("Unable to open file");

    // Init argcarriers
    ArgCarrier t1 = {1, false, semy, 10, file};

    // Init threads
    pthread_t thread;
    if (pthread_create(&thread, nullptr, thread_func, &t1) != 0)
        handle_error("Unable to create thread");

    // It's time to stop
    getchar();
    t1.stopThread = true;

    // Cleanup
    if (pthread_join(thread, nullptr) != 0) handle_error("Unable to join thread");
    if (sem_close(semy) != 0) handle_error("Unable to close semaphore");
    if (sem_unlink(SEM_NAME) != 0) handle_error("Unable to unlink semaphore");
    if (close(file) != 0) handle_error("Unable to close file");

    return EXIT_SUCCESS;
}
