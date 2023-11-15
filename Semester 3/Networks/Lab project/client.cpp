#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <iostream>
#include <pthread.h>
#include <unistd.h>

#define second 1000000

using std::string, std::cin, std::cout, std::getline;

string generateRandomString(int length)
{
    string result = "";

    for (int i = 0; i < length; i++)
    {
        char ch = 'a' + rand() % 26;
        result.push_back(ch);
    }

    return result;
}

void* handleUserInput(void* arg)
{
    int clientSocket = *((int*)arg), sendStatus;

    string message;

    while (1)
    {
        // getline(cin, message);

        int randomLength = rand() % 10 + 5;

        message = generateRandomString(randomLength);
        usleep(2 * second);

        uint16_t messageLength = message.size();
        uint16_t lengthCopy = messageLength;

        messageLength = htons(messageLength);

        send(clientSocket, &messageLength, sizeof(messageLength), 0);
        sendStatus = send(clientSocket, message.c_str(), lengthCopy * sizeof(char), 0);

        if (sendStatus == -1)
        {
            cout << "Failure on send. Error: " << strerror(errno) << std::endl;
            break;
        }
    }

    return NULL;
}


void* handleReceive(void* arg)
{
    int clientSocket = *((int*)arg), readStatus;

    u_int16_t lengthBuffer;
    char messageBuffer[500];

    while (1)
    {
        readStatus = recv(clientSocket, &lengthBuffer, sizeof(lengthBuffer), 0);

        if (readStatus == 0)
        {
            cout << "Connection closed by the server!\n";
            break;
        }

        else if (readStatus == -1)
        {
            cout << "Failure on receive. Error: " << strerror(errno) << std::endl;
            break;
        }
         
        lengthBuffer = ntohs(lengthBuffer);

        recv(clientSocket, messageBuffer, lengthBuffer, 0);
        messageBuffer[lengthBuffer] = '\0';

        printf("%s\n", messageBuffer);        
    }

    return NULL;
}



int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Incorrect usage. Please use as ./client [SERVER_IP] [SERVER_PORT].\n");
        exit(1);
    }

    int clientSocket;

    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(struct sockaddr_in));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(atoi(argv[2]));
    serverAddress.sin_addr.s_addr = inet_addr(argv[1]);

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket == -1)
    {
        printf("Failed to create socket!\n");
        exit(1);
    }

    if (connect(clientSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) == -1)
    {
        printf("Failed to connect to server!\n");
        exit(1);
    }
    printf("Welcome to the most basic chat app!\n");

    string clientName;

    printf("Your name is: ");
    getline(cin, clientName);

    uint16_t nameLength = clientName.size();
    uint16_t lengthCopy = nameLength;

    nameLength = htons(nameLength);

    send(clientSocket, &nameLength, sizeof(nameLength), 0);
    send(clientSocket, clientName.c_str(), lengthCopy * sizeof(char), 0);

    pthread_t inputThread, receiveThread;

    pthread_create(&inputThread, NULL, handleUserInput, &clientSocket);
    pthread_create(&receiveThread, NULL, handleReceive, &clientSocket);

    pthread_join(inputThread, NULL);
    pthread_join(receiveThread, NULL);

    close(clientSocket);

    return 0;
}