#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <errno.h>

#include <pthread.h>
#include <semaphore.h>

#include <string.h>

using namespace std;

const int BUFFER_SIZE = 100;

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while(0)

enum class ThreadType {
    Reader,
    Writer
};

static int filedes[2];

struct ArgCarrier
{
    uint threadNumber;
    bool stopThread;
    ThreadType type;
};

void* thread_func(void* arg)
{
    ArgCarrier* args = reinterpret_cast<ArgCarrier*>(arg);
    char buf[BUFFER_SIZE];
    int count = 0;
    while(!args->stopThread)
    {
        if (args->type == ThreadType::Writer)
        {
            int size = sprintf(buf, "Message %i from Thread %i", ++count, args->threadNumber);
            write(filedes[1], buf, size);
            sleep(1);
        } else if (args->type == ThreadType::Reader)
        {
            read(filedes[0], buf, BUFFER_SIZE);
            printf("Printed from Thread %i: %s\n", args->threadNumber, buf);
        }
    }
    printf("Thread %i was terminated\n", args->threadNumber);
    return nullptr;
}

int main(int argc, char const *argv[])
{
    if (pipe(filedes) != 0) handle_error("Pipe initialization failure");

    ArgCarrier t1 = {1, false, ThreadType::Writer};
    ArgCarrier t2 = {2, false, ThreadType::Reader};

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
    if (close(filedes[0]) != 0 || close(filedes[1]) != 0) handle_error("Unable to close pipe");

    return EXIT_SUCCESS;
}
