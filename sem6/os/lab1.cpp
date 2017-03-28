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
};

void* thread_func(void* arg)
{
    // Init thread
    ArgCarrier* args = reinterpret_cast<ArgCarrier*>(arg);

    // Main cycle
    while(!args->stopThread)
    {
        printf("%i", args->threadNumber);
        fflush(stdout);
        sleep(1);
    }

    // Terminate Thread
    printf("Thread %i was terminated\n", args->threadNumber);
    return nullptr;
}

int main(int argc, char const *argv[])
{
    // Init arguments
    ArgCarrier t1 = {1, false};
    ArgCarrier t2 = {2, false};

    // Init threads
    pthread_t thread1, thread2;
    if (pthread_create(&thread1, nullptr, thread_func, &t1) != 0)
        handle_error("Unable to create first thread");
    if (pthread_create(&thread2, nullptr, thread_func, &t2) != 0)
        handle_error("Unable to create second thread");

    // It's time to stop
    getchar();
    t1.stopThread = true;
    t2.stopThread = true;

    // Cleanup
    if (pthread_join(thread1, nullptr) != 0) handle_error("Unable to join first thread");
    if (pthread_join(thread2, nullptr) != 0) handle_error("Unable to join second thread");

    return EXIT_SUCCESS;
}
