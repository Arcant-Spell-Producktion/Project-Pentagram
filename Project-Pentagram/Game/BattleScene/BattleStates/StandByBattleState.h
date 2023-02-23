#pragma once
#include "BaseBattleState.h"

class StandByBattleState : public BaseBattleState
{
public:
    StandByBattleState() :BaseBattleState(BattleState::StandbyState) {}
    virtual void OnBattleStateIn()override;
    virtual void OnBattleStateUpdate(float dt) override;
    virtual void OnBattleStateOut() override;
};
