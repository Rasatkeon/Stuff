#include <stdlib.h> // Standard definitions
#include <stdio.h> // Standard IO
#include <unistd.h> // Constants
#include <errno.h> // Error handling
#include <pthread.h> // Multithreading

using namespace std;

// Error handling
#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while(0)

// Thread function arguments
struct ArgCarrier
{
    uint threadNumber;
    bool stopThread;
    pthread_mutex_t* mutexp;
};

void* thread_func(void* arg)
{
    // Init thread
    ArgCarrier* args = reinterpret_cast<ArgCarrier*>(arg);

    // Main cycle
    while(!args->stopThread)
    {
        //if (pthread_mutex_lock(args->mutexp) != 0) handle_error("Unable to lock mutex");
        if (pthread_mutex_trylock(args->mutexp) != 0) continue;
        for (int i = 0; i < 5; ++i)
        {
            printf("%i", args->threadNumber);
            fflush(stdout);
            sleep(1);
        }
        fflush(stdout);
        if (pthread_mutex_unlock(args->mutexp) != 0) handle_error("Unable to unlock mutex");
        sleep(1);
    }

    // Terminate thread
    printf("Thread %i was terminated\n", args->threadNumber);
    return nullptr;
}

int main(int argc, char const *argv[])
{
    pthread_mutex_t muty;
    if (pthread_mutex_init(&muty, nullptr) != 0) handle_error("Unable to init mutex");

    ArgCarrier t1 = {1, false, &muty};
    ArgCarrier t2 = {2, false, &muty};

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
    if (pthread_mutex_destroy(&muty) != 0) handle_error("Unable to destroy mutex");

    return EXIT_SUCCESS;
}
