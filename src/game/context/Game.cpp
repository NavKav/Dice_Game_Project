//
// Created by navid on 23/01/2023.
//

#include "Game.h"

using namespace std;

void Game::process(Player &player, Window &window) {
    if (_runServer) {
        //startServer();
        _runServer = false;
    }

    _client.send("salut");
    /*************************************************************************/
    /*************************  INDEX  ***************************************/
    /*************************************************************************/
    static UnitIndex unitIndex;
    static BlockIndex blockIndex;
    /*************************************************************************/
    /*************************  INITIALIZATION  ******************************/
    /*************************************************************************/
    srand(time(NULL));
    _frameRate.display(window);

    static MapView mapView(window, _mapGenerator, blockIndex);
    static double x = 0, y = 0;
    static bool firstTime = true;
    if (firstTime) {
        window.drawOn(BACKGROUND);
        mapView.displayFromCoordinate(x, y);
    }
    /*************************************************************************/
    /*************************  UNITS TESTS  *********************************/
    /*************************************************************************/
    static HeroModel heroModel(player, unitIndex.get("paladin"), x, y);
    static HeroView _heroView(heroModel, window);

    static NPCModel npcModel1(unitIndex.get("golem"), heroModel);
    static NPCView npc1(window, npcModel1);
    static NPCModel npcModel2(unitIndex.get("golem"), heroModel);
    static NPCView npc2(window, npcModel2);
    static NPCModel npcModel3(unitIndex.get("golem"), heroModel);
    static NPCView npc3(window, npcModel3);
    static NPCModel npcModel4(unitIndex.get("golem"), heroModel);
    static NPCView npc4(window, npcModel4);
    static NPCModel npcModel5(unitIndex.get("golem"), heroModel);
    static NPCView npc5(window, npcModel5);
    static NPCModel npcModel6(unitIndex.get("golem"), heroModel);
    static NPCView npc6(window, npcModel6);
    static NPCModel npcModel7(unitIndex.get("golem"), heroModel);
    static NPCView npc7(window, npcModel7);
    static NPCModel npcModel8(unitIndex.get("golem"), heroModel);
    static NPCView npc8(window, npcModel8);
    static NPCModel npcModel9(unitIndex.get("golem"), heroModel);
    static NPCView npc9(window, npcModel9);
    static NPCModel npcModel10(unitIndex.get("golem"), heroModel);
    static NPCView npc10(window, npcModel10);
    static NPCModel npcModel11(unitIndex.get("golem"), heroModel);
    static NPCView npc11(window, npcModel11);
    static NPCModel npcModel12(unitIndex.get("golem"), heroModel);
    static NPCView npc12(window, npcModel12);
    static NPCModel npcModel13(unitIndex.get("golem"), heroModel);
    static NPCView npc13(window, npcModel13);
    static NPCModel npcModel14(unitIndex.get("golem"), heroModel);
    static NPCView npc14(window, npcModel14);
    static NPCModel npcModel15(unitIndex.get("golem"), heroModel);
    static NPCView npc15(window, npcModel15);
    static NPCModel npcModel16(unitIndex.get("golem"), heroModel);
    static NPCView npc16(window, npcModel16);
    static UnitModelHandler unitModelHandler;
    static UnitViewHandler unitViewHandler(window);


    if (firstTime) {
        unitModelHandler.add(&npcModel1);
        unitModelHandler.add(&npcModel2);
        unitModelHandler.add(&npcModel3);
        unitModelHandler.add(&npcModel4);
        unitModelHandler.add(&npcModel5);
        unitModelHandler.add(&npcModel6);
        unitModelHandler.add(&npcModel7);
        unitModelHandler.add(&npcModel8);
        unitModelHandler.add(&npcModel9);
        unitModelHandler.add(&npcModel10);
        unitModelHandler.add(&npcModel11);
        unitModelHandler.add(&npcModel12);
        unitModelHandler.add(&npcModel13);
        unitModelHandler.add(&npcModel14);
        unitModelHandler.add(&npcModel15);
        unitModelHandler.add(&npcModel16);

        unitModelHandler.add(&heroModel);

        unitViewHandler.add(&npc1);
        unitViewHandler.add(&npc2);
        unitViewHandler.add(&npc3);
        unitViewHandler.add(&npc4);
        unitViewHandler.add(&npc5);
        unitViewHandler.add(&npc6);
        unitViewHandler.add(&npc7);
        unitViewHandler.add(&npc8);
        unitViewHandler.add(&npc9);
        unitViewHandler.add(&npc10);
        unitViewHandler.add(&npc11);
        unitViewHandler.add(&npc12);
        unitViewHandler.add(&npc13);
        unitViewHandler.add(&npc14);
        unitViewHandler.add(&npc15);
        unitViewHandler.add(&npc16);

        unitViewHandler.add(&_heroView);

        firstTime = false;
    }

    unitModelHandler.play();
    mapView.shiftMap(heroModel.getX(), heroModel.getY(), heroModel.getSpeed());
    unitViewHandler.displayAll(heroModel.getX(), heroModel.getY());

    /*************************************************************************/
    /*************************  DISPLAY **************************************/
    /*************************************************************************/

    window.refresh();
}

void Game::startServer() {
    std::future<void> future_result = std::async(std::launch::async, []() {
        system(R"("send C:\Users\navid\CLionProjects\ARPG_StoryBoard\cmake-build-debug\Dice_Game_Project.exe" _server)");
    });
}
