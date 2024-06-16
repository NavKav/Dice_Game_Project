#include "online/server.h"
#include "core/Window.h"
#include "game/menu/MenuWindowContent.h"
#include "game/context/GameWindowContent.h"

#undef main

using namespace std;

#include <string>
#include <iostream>
#include <filesystem>
#include <future>

using namespace std::filesystem;


int main( int argc, char *argv[] )
{
    if (argc == 2 && !strcmp(argv[1], "_server")) {
        Server server(1998);
        server.start();
        return 0;
    }

    // (32 x 40) x (32 x 24)
    Window window("ARPG_StoryBoard", 32 * 40, 32 * 24);

    //Player p(window, new MenuWindowContent());
    //Player p(window, new OptionWindowContent());
    Player p(window, new GameWindowContent());
    //Player p(window, nullptr);
    p.start();

    return 0;
}