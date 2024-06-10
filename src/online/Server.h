//
// Created by navid on 18/03/2024.
//

#ifndef ARPG_STORYBOARD_SERVER_H
#define ARPG_STORYBOARD_SERVER_H

#include <iostream>
#include "OSMultiplayerDependencies.h"
#include "core/Player.h"
#include "game/map/MapView.h"
#include "util/FrameRate.h"
#include "game/unit/NPCView.h"
#include "game/unit/UnitViewHandler.h"
#include "game/unit/UnitModelHandler.h"
#include "game/unit/HeroModel.h"
#include "game/unit/HeroView.h"
#include "game/index/UnitIndex.h"
#include "game/index/BlockIndex.h"


class Server {
public:
    Server(int port);
    ~Server();
    void start();

private :
    SOCKET _serverSocket;
    sockaddr_in _server{}, _client{};
};

#endif //ARPG_STORYBOARD_SERVER_H
