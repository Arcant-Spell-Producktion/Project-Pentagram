#pragma once
#include "Game/BattleScene/BattleStates/BaseBattleState.h"

class SetupTestState : public BaseBattleState
{
public:
    SetupTestState() :BaseBattleState(BattleState::SetupState) {}
    virtual void OnBattleStateIn() override;
    virtual void OnBattleStateUpdate(float dt) override;
    virtual void OnBattleStateOut() override;
};
