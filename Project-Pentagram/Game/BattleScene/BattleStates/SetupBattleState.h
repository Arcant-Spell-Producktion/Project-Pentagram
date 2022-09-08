#pragma once
#include "BaseBattleState.h"
#include "Game/BattleScene/SpellCaster/PlayerController.h"
#include "Game/GameData/RuntimeGameData.h"

class SetupBattleState : public BaseBattleState
{
public:
    SetupBattleState() :BaseBattleState(BattleState::SetupState) {}
    virtual void OnBattleStateIn(BattleManager* currentBattleManager) override
    {
        currentBattleManager->AddCaster(new PlayerController(*(RuntimeGameData::GetInstance()->Player)));
        currentBattleManager->AddCaster(new CasterController({ Element::Debug,CasterPosition::CasterB,1,1 }));
    }
    virtual void OnBattleStateOut() override {}
};
