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

void Client::startCommunication() {
    char message[256];
    printf("Enter message: ");
    cin.getline(message, 256);
    while (sendto(_clientSocket, message, strlen(message), 0, (sockaddr*)&_server, sizeof(sockaddr_in)) == SOCKET_ERROR) {
        cout << "sendto() failed with error code: " << getSocketError() << endl;
        exit(EXIT_FAILURE);
    }
    char answer[256] = {};
    int slen = sizeof(sockaddr_in);
    int answer_length;
    while ((answer_length = recvfrom(_clientSocket, answer, 256, 0, (sockaddr*)&_server, &slen)) == SOCKET_ERROR) {
        cout << "recvfrom() failed with error code: " << getSocketError() << endl;
        exit(EXIT_FAILURE);
    }
    cout << "Server's response: " << answer << "\n";
}