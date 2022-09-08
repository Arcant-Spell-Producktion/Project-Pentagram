#pragma once
#include <vector>
#include "Game/BattleScene/SpellCaster/CasterController.h"
#include "Game/BattleScene/SpellTimeline/SpellTimeline.h"

class BattleSceneData
{
public:
    int CurrentCasterIndex = 0;
    std::vector<CasterController*> Casters;
    SpellTimeline Timeline;

    void AddCaster(CasterController* controller) { Casters.push_back(controller); }
};