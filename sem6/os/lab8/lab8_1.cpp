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

int listenerSocket;
int dataSocket;

queue<string> requestQueue;
queue<string> responseQueue;
pthread_mutex_t requestMuty;
pthread_mutex_t responseMuty;


bool stopReceivingThread  = false;
bool stopProcessingThread = false;
bool stopRespondingThread = false;
bool stopListeningThread  = false;

bool connectionEstablished = false;

pthread_t ReceivingThread;
pthread_t ProcessingThread;
pthread_t RespondingThread;
pthread_t ListeningThread;

void* receiveRequest(void* stopFlag) {
    char buf[BUFF_SIZE];
    while(!*reinterpret_cast<bool*>(stopFlag)) {
        auto recres = recv(dataSocket, buf, BUFF_SIZE, 0);
        if (recres == -1) {
            auto err = errno;
            if (err == EAGAIN || err == EWOULDBLOCK) continue;
            perror("Receiving thread: Couldn't receive");
            sleep(1);
        } if (recres == 0) {
            stopReceivingThread = true;
            stopProcessingThread = true;
            stopRespondingThread = true;
        } else {
            printf("Received request: %s\n", buf);
            requestQueue.push(string(buf));
        }
    }
    printf("Receiving thread terminated.\n");
    return nullptr;
}

void* processRequest(void* stopFlag) {
    string request;
    string response;
    uint count = 0;
    while(!*reinterpret_cast<bool*>(stopFlag)) {
        if(requestQueue.empty()) {
            sleep(1);
            continue;
        }
        pthread_mutex_lock(&requestMuty);
            request = requestQueue.front();
            requestQueue.pop();
        pthread_mutex_unlock(&requestMuty);
        response = request + "Request #" + to_string(++count);
        responseQueue.push(response);
    }
    printf("Processing thread terminated.\n");
    return nullptr;
}

void* respond(void* stopFlag) {
    string response;
    while(!*reinterpret_cast<bool*>(stopFlag)) {
        if (responseQueue.empty()) {
            sleep(1);
            continue;
        }

        pthread_mutex_lock(&responseMuty);
            response = responseQueue.front();
            responseQueue.pop();
        pthread_mutex_unlock(&responseMuty);

        send(dataSocket, response.c_str(), response.size(), 0);
    }
    printf("Responding thread terminated.\n");
    return nullptr;
}

void* listen(void* stopFlag) {
//    sockaddr addr;
//    socklen_t  len;
    printf("Start listening thread.\n");
    while(!*reinterpret_cast<bool*>(stopFlag)) {
        dataSocket = accept(listenerSocket, nullptr, nullptr);
        if (dataSocket == -1) {
            perror("Unable to accept connection");
            sleep(1);
            continue;
        } else {
            connectionEstablished = true;
            fcntl(dataSocket, F_SETFL, O_NONBLOCK);

            if (pthread_mutex_init(&requestMuty, nullptr) < 0)
                handle_error("Unable to create request queue mutex");
            if (pthread_mutex_init(&responseMuty, nullptr) < 0)
                handle_error("Unable to create response queue mutex");
            pthread_create(&ReceivingThread, nullptr, receiveRequest, &stopReceivingThread);
            pthread_create(&ProcessingThread, nullptr, processRequest, &stopProcessingThread);
            pthread_create(&RespondingThread, nullptr, respond, &stopRespondingThread);

            stopListeningThread = true;
        }
    }
    printf("Listening thread terminated.\n");
}

int main(int argc, char const *argv[])
{
    // TODO: check if additional threads were created
    //
    listenerSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listenerSocket < 0)
        handle_error("Unable to create listener socket");

    if (fcntl(listenerSocket, F_SETFL, O_NONBLOCK) == -1)
        handle_error("Unable to set nonblock to listener socket");

    sockaddr_in addr = {AF_INET, htons(8080), INADDR_ANY};

    if (bind(listenerSocket, (sockaddr*)&addr, sizeof(addr)) < 0)
        handle_error("Unable to bind listener socket");

    printf("Begin listening...\n");
    if (listen(listenerSocket, 1) < 0)
        handle_error("Error listening to socket");

    if (pthread_create(&ListeningThread, nullptr, listen, &stopListeningThread) != 0)
        handle_error("Unable to create listening thread");

    getchar();

    stopReceivingThread  = true;
    stopProcessingThread = true;
    stopRespondingThread = true;
    stopListeningThread  = true;

    if (connectionEstablished) {
        pthread_join(ReceivingThread, nullptr);
        pthread_join(ProcessingThread, nullptr);
        pthread_join(RespondingThread, nullptr);

        if (pthread_mutex_destroy(&requestMuty) < 0)
            handle_error("Unable to destroy request queue mutex");
        if (pthread_mutex_destroy(&responseMuty) < 0)
            handle_error("Unable to destroy response queue mutex");

        shutdown(dataSocket, SHUT_RDWR);
        close(dataSocket);
    }
    pthread_join(ListeningThread,  nullptr);
    close(listenerSocket);
    // Close, Shutdown
    printf("Shutdown sever.\n");

    return EXIT_SUCCESS;
}
