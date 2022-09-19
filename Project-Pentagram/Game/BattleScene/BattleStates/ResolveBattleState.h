#pragma once
#include "BaseBattleState.h"

class ResolveBattleState : public BaseBattleState
{
public:
    ResolveBattleState() :BaseBattleState(BattleState::ResolveState) {}
    virtual void OnBattleStateIn()override;
    virtual void OnBattleStateUpdate(float dt) override;
    virtual void OnBattleStateOut() override;

};
