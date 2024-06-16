//
// Created by navid on 18/03/2024.
//

#include "Server.h"

using namespace std;

Server::Server(int port) {
    // initialise winsock
    socketInitialisation();
    // create a socket
    if ((_serverSocket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        cout << "Could not create socket: " << getSocketError() << endl;
        exit(-1);
    }

    // prepare the sockaddr_in structure
    _server.sin_family = AF_INET;
    _server.sin_addr.s_addr = INADDR_ANY;
    _server.sin_port = htons(port);

    // bind
    if (bind(_serverSocket, (sockaddr*)&_server, sizeof(_server)) == SOCKET_ERROR) {
        cout <<"Bind failed with error code: "<< getSocketError() << endl;
        exit(EXIT_FAILURE);
    }
    puts("Bind done.");
}

Server::~Server() {
    closeSocket(_serverSocket);
}

void Server::start() {
    /*************************************************************************/
    /*************************  INDEX  ***************************************/
    /*************************************************************************/
    UnitIndex unitIndex;
    BlockIndex blockIndex;

    /*************************************************************************/
    /*************************  INITIALIZATION  ******************************/
    /*************************************************************************/
    double x = 0, y = 0;
    bool firstTime = true;

    /*************************************************************************/
    /*************************  UNITS TESTS  *********************************/
    /*************************************************************************/


    /*************************************************************************/
    /*************************  RUN SERVER  **********************************/
    /*************************************************************************/
    /*bool exitRequested = false;
    while (!exitRequested) {


    }*/

    printf("Waiting for data...");
    //fflush(stdout);
    char message[512] = {};

    // try to receive some data, this is a blocking call
    int slen = sizeof(sockaddr_in);
    while (true) {
        if ((recvfrom(_serverSocket, message, 512, 0, (sockaddr *) &_client, &slen)) == SOCKET_ERROR) {
            printf("recvfrom() failed with error code: %d", WSAGetLastError());
            exit(0);
        }

        // print details of the client/peer and the data received
        printf("Received packet from %s:%d\n", inet_ntoa(_client.sin_addr), ntohs(_client.sin_port));
        printf("Data: %s\n", message);
    }


    // reply to the client with the same data
    /*if (sendto(_serverSocket, message, strlen(message), 0, (sockaddr*)&_client, sizeof(sockaddr_in)) == SOCKET_ERROR) {
        printf("sendto() failed with error code: %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }*/
}