#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>

#include <pthread.h>

#include <sys/socket.h>
#include <queue>
#include <string>
#include <netinet/in.h>

#define BUFF_SIZE 100

using namespace std;

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while(0)

int dataSocket;

bool stopConnectingThread  = false;
bool stopSendingThread = false;
bool stopReceivingThread  = false;

bool connectionEstablished = false;

pthread_t SendingThread;
pthread_t RecieveingThread;
pthread_t ConnectingThread;

void* sendRequest(void* stopFlag) {
    char buf[BUFF_SIZE];
    int request_num = 0;
    while(!*reinterpret_cast<bool*>(stopFlag)) {
        int size = sprintf(buf, "Request #%i.", request_num++);
        send(dataSocket, buf, size, 0);
        sleep(1);
    }
    printf("Sending thread terminated.\n");
    return nullptr;
}

void* receiveResponse(void* stopFlag) {
    char buf[BUFF_SIZE];
    while(!*reinterpret_cast<bool*>(stopFlag)) {
        auto recres = recv(dataSocket, buf, BUFF_SIZE, 0);
        if (recres == -1) {
            auto err = errno;
            if (err == EAGAIN || err == EWOULDBLOCK) continue;
            perror("Receiving thread: Couldn't receive");
            sleep(1);
        } if (recres == 0) {
            stopSendingThread = true;
            stopReceivingThread = true;
        } else
            printf("Response is:%s\n", buf);
    }
    printf("Receiving thread terminated.\n");
    return nullptr;
}

void* connect(void* stopFlag) {
    sockaddr_in inaddr = {AF_INET, htons(8080), INADDR_ANY};
    while(!*reinterpret_cast<bool*>(stopFlag)) {
        printf("Trying to connect...\n");
        int res = connect(dataSocket, (sockaddr*)&inaddr, sizeof(inaddr));
        if (res == 0) {
            connectionEstablished = true;
            pthread_create(&SendingThread, nullptr, sendRequest, &stopSendingThread);
            pthread_create(&RecieveingThread, nullptr, receiveResponse, &stopReceivingThread);
            break;
        }
        sleep(1);
    }
    printf("Connecting thread terminated.\n");
    return nullptr;
}

int main(int argc, char const *argv[])
{
    dataSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (dataSocket < 0)
        handle_error("Unable to create data socket");

    fcntl(dataSocket, F_SETFL, O_NONBLOCK);

    if (pthread_create(&ConnectingThread, nullptr, connect, &stopConnectingThread) != 0)
        handle_error("Unable to create connecting thread");

    getchar();

    stopConnectingThread = true;
    stopSendingThread = true;
    stopReceivingThread = true;

    pthread_join(ConnectingThread, nullptr);
    if (connectionEstablished) {
        pthread_join(SendingThread, nullptr);
        pthread_join(RecieveingThread, nullptr);
    }

    shutdown(dataSocket, SHUT_RDWR);
    close(dataSocket);

    printf("Shutdown client.\n");

    return EXIT_SUCCESS;
}
