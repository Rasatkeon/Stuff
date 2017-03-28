#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <errno.h>

#include <pthread.h>
#include <semaphore.h>

using namespace std;

#define SHARED_WITHIN_PROCESS 0

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while(0)

struct ArgCarrier
{
    uint threadNumber;
    bool stopThread;
    sem_t* semp;
    time_t secToWait;
};

void* thread_func(void* arg)
{
    ArgCarrier* args = reinterpret_cast<ArgCarrier*>(arg);
    while(!args->stopThread)
    {
        // if (sem_wait(args->semp) != 0) handle_error("Unable to wait");
        // if (sem_trywait(args->semp) != 0) {
        //     if (errno == EAGAIN) continue;
        //     else handle_error("Unable to trywait");
        // }
        timespec ts;
        if (clock_gettime(CLOCK_REALTIME, &ts) != 0) handle_error("Unable to get time");
        ts.tv_sec += args->secToWait;
        if (sem_timedwait(args->semp, &ts) != 0)
        {
            if (errno == ETIMEDOUT)
            {
                printf("Thread %i timed out\n", args->threadNumber);
                break;
            } else handle_error("Unable to wait");
        }
        for (int i = 0; i < 5; ++i)
        {
            printf("%i", args->threadNumber);
            fflush(stdout);
            sleep(1);
        }
        sem_post(args->semp);
        sleep(1);
    }
    printf("Thread %i was terminated\n", args->threadNumber);
    return nullptr;
}

int main(int argc, char const *argv[])
{
    sem_t semy;
    if (sem_init(&semy, SHARED_WITHIN_PROCESS, 1) != 0) handle_error("Unable to init semaphore");

    ArgCarrier t1 = {1, false, &semy, 10};
    ArgCarrier t2 = {2, false, &semy, 3};

    pthread_t thread1, thread2;
    if (pthread_create(&thread1, nullptr, thread_func, &t1) != 0)
        handle_error("Unable to create first thread");
    if (pthread_create(&thread2, nullptr, thread_func, &t2) != 0)
        handle_error("Unable to create second thread");

    getchar();
    t1.stopThread = true;
    t2.stopThread = true;

    if (pthread_join(thread1, nullptr) != 0) handle_error("Unable to join first thread");
    if (pthread_join(thread2, nullptr) != 0) handle_error("Unable to join second thread");
    if (sem_destroy(&semy) != 0) handle_error("Unable to destroy semaphore");

    return EXIT_SUCCESS;
}
