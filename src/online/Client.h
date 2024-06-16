//
// Created by navid on 24/03/2024.
//

#ifndef ARPG_STORYBOARD_CLIENT_H
#define ARPG_STORYBOARD_CLIENT_H

#include "OSMultiplayerDependencies.h"

class Client {
public:
    Client(int port, const std::string& ip);
    ~Client();
    void send(std::string s);

private:
    SOCKET _clientSocket;
    sockaddr_in _server;
};


#endif //ARPG_STORYBOARD_CLIENT_H
