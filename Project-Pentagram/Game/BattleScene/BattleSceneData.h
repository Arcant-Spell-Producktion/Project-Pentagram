#pragma once
#include <vector>
#include "Game/BattleScene/SpellCaster/CasterController.h"
#include "Game/BattleScene/SpellTimeline/SpellTimeline.h"
#include "Game/BattleScene/GameObject/WillCompareController.h"
#include "Game/BattleScene/GameObject/PentagramObject/PentagramController.h"
#include "Game/Objects/StageObject.h"
#include "Game/Objects/GameOverUI.h"
#include "Game/Objects/TextBox.h"

class BattleSceneData
{
public:
    int CurrentCasterIndex = 0;
    std::vector<CasterController*> Casters;

    StageObject* Stage = nullptr;

    SpellTimeline Timeline;

    PentragramController* Pentagram = nullptr;

    WillCompareController* WillCompare = nullptr;

    GameOverUI* GameOverUI = nullptr;

    TextBox* Texts = nullptr;

    void AddCaster(CasterController* controller) { Casters.push_back(controller); }

    void SetIsShowCasterDetail(bool active)
    {
        for (CasterController* caster : Casters)
        {
            // If caster is enemy => Don't show CasterDetail
            if (caster->GetCasterManager()->Data().Position() == CasterPosition::CasterB) { continue; }
            
            caster->SetIsShowCasterDetail(active);
        }
    }
    bool IsShowCasterDetail() { return Casters[0]->IsShowCasterDetail(); }

    CasterController* GetCaster(CasterPosition position);
    CasterController* GetCurrentCaster() { return Casters[CurrentCasterIndex]; }
    CasterController* GetNextCaster() { return Casters[(CurrentCasterIndex + 1) % Casters.size()]; }

    void HideCasterUI();

    void StandbyAllCaster();

    bool IsAllCasterIdle();

    void StartRound();
    void EndCastPhase();
    void EndRound();
};