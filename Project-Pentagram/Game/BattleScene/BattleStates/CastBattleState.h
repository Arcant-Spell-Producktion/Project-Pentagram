#pragma once
#include "BaseBattleState.h"

enum class CastUpdateState
{
    Casting,
    Casted,
};

class CastBattleState : public BaseBattleState
{
public:
    CastBattleState() :BaseBattleState(BattleState::CastState) {}
    virtual void OnBattleStateIn()override;
    virtual void OnBattleStateUpdate(float dt) override;
    virtual void OnBattleStateOut() override;
};
