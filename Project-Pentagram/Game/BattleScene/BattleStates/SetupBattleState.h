#pragma once
#include "BaseBattleState.h"

class SetupBattleState : public BaseBattleState
{
public:
    SetupBattleState() :BaseBattleState(BattleState::SetupState) {}
    virtual void OnBattleStateIn()override;
    virtual void OnBattleStateUpdate(float dt) override;
    virtual void OnBattleStateOut() override;
};
