#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <errno.h>

#include <pthread.h>
#include <semaphore.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

using namespace std;

#define FIFO_NAME "./fifo"
#define DEF_PERM 0644
#define PROG_NUM '2'
#define BUFFER_SIZE 100

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while(0)

struct ArgCarrier
{
    uint threadNumber;
    bool stopThread;
    int fifo;
};

void* thread_func(void* arg)
{
    ArgCarrier* args = reinterpret_cast<ArgCarrier*>(arg);
    char buf[BUFFER_SIZE];
    while(!args->stopThread)
    {
        if (read(args->fifo, buf, BUFFER_SIZE) == 0) 
        {
            printf("Waiting for input\n");
            sleep(1);
            continue;
        }
        printf("Printed from Process %c: %s\n", PROG_NUM, buf);
        sleep(1);
    }
       
    printf("Thread %i was terminated\n", args->threadNumber);
    return nullptr;
}

int main(int argc, char const *argv[])
{
    unlink(FIFO_NAME);

    // Init fifo
    if (mkfifo(FIFO_NAME, DEF_PERM) != 0) handle_error("Unable to make fifo");
    int fif = open(FIFO_NAME, O_RDONLY | O_NONBLOCK);
    if (fif == -1) handle_error("Unable to open fifo");

    // Init argcarrier
    ArgCarrier t1 = {1, false, fif};

    // Init threads
    pthread_t thread;
    if (pthread_create(&thread, nullptr, thread_func, &t1) != 0)
        handle_error("Unable to create thread");

    // It's time to stop
    getchar();
    t1.stopThread = true;

    // Cleanup
    if (pthread_join(thread, nullptr) != 0) handle_error("Unable to join thread");
    if (close(fif) != 0) handle_error("Unable to close fifo");
    if (unlink(FIFO_NAME) != 0) handle_error("Unable to unlink fifo");

    return EXIT_SUCCESS;
}
