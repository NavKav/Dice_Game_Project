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


    bool exitRequested = false;
    while (!exitRequested) {


    }
}