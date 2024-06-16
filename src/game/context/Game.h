//
// Created by navid on 23/01/2023.
//

#ifndef ARPG_STORYBOARD_GAME_H
#define ARPG_STORYBOARD_GAME_H

#include <future>
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
#include "online/Client.h"

class Game {
public :
    void process(Player& player, Window& window);
    void startServer();
private :
    FrameRate _frameRate;
    MapModel _mapGenerator = MapModel(1);
    Client _client = Client(1998, "127.0.0.1");

    bool _runServer = true;
};


#endif //ARPG_STORYBOARD_GAME_H
