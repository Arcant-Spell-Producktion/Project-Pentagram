#pragma once
#include "Game/BattleScene/BattleStates/BaseBattleState.h"

class SetupTutorialState : public BaseBattleState
{
public:
    SetupTutorialState() :BaseBattleState(BattleState::SetupState) {}
    virtual void OnBattleStateIn()override;
    virtual void OnBattleStateUpdate(float dt) override;
    virtual void OnBattleStateOut() override;
};
