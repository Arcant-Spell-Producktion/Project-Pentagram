#pragma once
#include <vector>
#include "Game/BattleScene/SpellCaster/CasterController.h"
#include "Game/BattleScene/SpellTimeline/SpellTimeline.h"
#include "Game/BattleScene/GameObject/PentagramController.h"

class BattleSceneData
{
public:
    int CurrentCasterIndex = 0;
    std::vector<CasterController*> Casters;
    SpellTimeline Timeline;

    PentragramController* Pentagram;

    void AddCaster(CasterController* controller) { Casters.push_back(controller); }

    CasterController* GetCaster(CasterPosition position);
    CasterController* GetCurrentCaster() { return Casters[CurrentCasterIndex]; }
    CasterController* GetNextCaster() { return Casters[(CurrentCasterIndex + 1) % Casters.size()]; }

    void StandbyAllCaster();
};