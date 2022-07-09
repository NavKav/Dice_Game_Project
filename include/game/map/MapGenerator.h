//
// Created by navid on 11/06/2022.
//

#ifndef ARPG_STORYBOARD_MAPGENERATOR_H
#define ARPG_STORYBOARD_MAPGENERATOR_H

#include <iostream>
#include <stdlib.h>
#include <utility>
#include "ground.h"
#include "game/map/PerlinNoise.h"

typedef unsigned int Uint;

class MapGenerator {
public:
    MapGenerator(){};
    MapGenerator(unsigned int X, unsigned int Y, unsigned int seed);
    ~MapGenerator();
    void generate() const;
    void blank();
    void display();
    Uint& operator()(unsigned int x, unsigned int y);
    bool sameTile(unsigned int x, unsigned int y, unsigned int d);
        private:
    unsigned int _X, _Y;
    unsigned int _seed;
    Uint** _mapGround;
};


#endif //ARPG_STORYBOARD_MAPGENERATOR_H
