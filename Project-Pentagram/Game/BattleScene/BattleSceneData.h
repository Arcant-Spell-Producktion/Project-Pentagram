#pragma once
#include <vector>
#include "Game/BattleScene/SpellCaster/CasterController.h"
#include "Game/BattleScene/SpellTimeline/SpellTimeline.h"
#include "Game/BattleScene/GameObject/WillCompareController.h"
#include "Game/BattleScene/GameObject/PentagramObject/PentagramController.h"

class BattleSceneData
{
public:
    int CurrentCasterIndex = 0;
    std::vector<CasterController*> Casters;

    SpellTimeline Timeline;
    PentragramController* Pentagram = nullptr;

    WillCompareController* WillCompare = nullptr;

    void AddCaster(CasterController* controller) { Casters.push_back(controller); }

    void SetIsShowCasterDetail(bool active)
    {
        for (CasterController* caster : Casters)
        {
            caster->SetIsShowCasterDetail(active);
        }
    }
    bool IsShowCasterDetail() { return Casters[0]->IsShowCasterDetail(); }

    CasterController* GetCaster(CasterPosition position);
    CasterController* GetCurrentCaster() { return Casters[CurrentCasterIndex]; }
    CasterController* GetNextCaster() { return Casters[(CurrentCasterIndex + 1) % Casters.size()]; }

    void StandbyAllCaster();
};