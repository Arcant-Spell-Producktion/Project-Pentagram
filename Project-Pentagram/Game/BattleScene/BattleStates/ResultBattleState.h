#pragma once
#include "BaseBattleState.h"

class ResultBattleState : public BaseBattleState
{
public:
    ResultBattleState() :BaseBattleState(BattleState::ResultState) {}
    virtual void OnBattleStateIn()override;
    virtual void OnBattleStateUpdate(float dt) override;
    virtual void OnBattleStateOut() override;
};
