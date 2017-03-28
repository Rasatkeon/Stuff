#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <errno.h>

#include <pthread.h>
#include <mqueue.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

using namespace std;

#define MQ_NAME "/lab7mq"
#define DEF_PERM 0644
#define PROG_NUM 2
#define BUFFER_SIZE 128
static uint MAX_PRIORITY = 0;

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while(0)

struct ArgCarrier
{
    uint threadNumber;
    bool stopThread;
    mqd_t mq;
};

void* thread_func(void* arg)
{
    ArgCarrier* args = reinterpret_cast<ArgCarrier*>(arg);
    mq_attr mqa;
    mq_getattr(args->mq, &mqa);
    char buf[BUFFER_SIZE];
    while(!args->stopThread)
    {
        if (mq_receive(args->mq, buf, mqa.mq_msgsize, &MAX_PRIORITY) == -1) {
            perror("Unable to receive from mq");
            sleep(1);
            continue;
        }
        printf("Printed from Process %i: %s\n", PROG_NUM, buf);
        sleep(1);
    }
       
    printf("Thread %i was terminated\n", args->threadNumber);
    return nullptr;
}

int main(int argc, char const *argv[])
{
    // Init message queue
    mqd_t mq = mq_open(MQ_NAME, O_CREAT | O_NONBLOCK | O_RDWR, DEF_PERM, nullptr);
    if (mq == mqd_t(-1)) handle_error("Unable to open mq");

    printf("Mqd: %i\n", int(mq));
    // Init argcarrier
    ArgCarrier t1 = {1, false, mq};

    // Init threads
    pthread_t thread;
    if (pthread_create(&thread, nullptr, thread_func, &t1) != 0)
        handle_error("Unable to create thread");

    // It's time to stop
    getchar();
    t1.stopThread = true;

    // Cleanup
    if (pthread_join(thread, nullptr) != 0) handle_error("Unable to join thread");
    if (mq_close(mq) != 0) handle_error("Unable to close mq");
    if (mq_unlink(MQ_NAME) != 0) handle_error("Unable to unlink mq");

    return EXIT_SUCCESS;
}
