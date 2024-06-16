//
// Created by navid on 24/03/2024.
//

#include "Client.h"

using namespace std;

Client::Client(int port, const string& ip) {
    socketInitialisation();

    if ((_clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR) {
        cout << "socket() failed with error code: " << getSocketError() << endl;
        exit(EXIT_FAILURE);
    }

    memset((char*)&_server, 0, sizeof(_server));
    _server.sin_family = AF_INET;
    _server.sin_port = htons(port);
    _server.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
}

Client::~Client() {
    closeSocket(_clientSocket);
}

void Client::send(string s) {
    char * message = const_cast<char *>(s.c_str());
    while (sendto(_clientSocket, message, strlen(message), 0, (sockaddr*)&_server, sizeof(sockaddr_in)) == SOCKET_ERROR) {
        cout << "sendto() failed with error code: " << getSocketError() << endl;
        exit(EXIT_FAILURE);
    }
    /*while ((answer_length = recvfrom(_clientSocket, answer, 256, 0, (sockaddr*)&_server, &slen)) == SOCKET_ERROR) {
        cout << "recvfrom() failed with error code: " << getSocketError() << endl;
        exit(EXIT_FAILURE);
    }*/
}