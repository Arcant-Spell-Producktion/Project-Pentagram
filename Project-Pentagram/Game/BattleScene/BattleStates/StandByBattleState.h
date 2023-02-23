#pragma once
#include "BaseBattleState.h"

class StandByBattleState : public BaseBattleState
{
private:
    float Timer = 0.0f;
    float MaxTime = 3.0f;
public:
    StandByBattleState() :BaseBattleState(BattleState::StandbyState) {}
    virtual void OnBattleStateIn()override;
    virtual void OnBattleStateUpdate(float dt) override;
    virtual void OnBattleStateOut() override;
};
