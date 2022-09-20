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

    PentragramController* pentragramController;

    CasterController* GetCaster(CasterPosition position) 
    {
        CasterController* caster = nullptr;
        for (auto c: Casters)
        {
            if (c->GetSpellCaster()->GetCasterData()->GetPosition() == position)
            {
                caster = c;
                break;
            }
        }
        return caster;
    }
    CasterController* GetCurrentCaster() { return Casters[CurrentCasterIndex]; }
    CasterController* GetNextCaster() { return Casters[(CurrentCasterIndex + 1) % Casters.size()]; }
    void AddCaster(CasterController* controller) { Casters.push_back(controller); }
    void StandbyAllCaster()
    {
        for (auto caster : Casters)
        {
            caster->SetState(CasterState::Idle);
            caster->GetSpellCaster()->ResetMana();
            caster->UpdateCasterUI();
        }
    }
};