//
// Created by navid on 21/01/2023.
//

#ifndef ARPG_STORYBOARD_NPCMODEL_H
#define ARPG_STORYBOARD_NPCMODEL_H

#include "UnitModel.h"

class NPCModel : public UnitModel {
public :
    NPCModel();
    NPCModel(double x, double y);
    void initialize() override;
    UnitDecision choice();
private :
};


#endif //ARPG_STORYBOARD_NPCMODEL_H
