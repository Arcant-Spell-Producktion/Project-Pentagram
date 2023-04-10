#pragma once
#include "BaseBattleState.h"



class CastBattleState : public BaseBattleState
{
public:
    enum class CastUpdateState
    {
        Casting,
        Casted,
    };

    CastBattleState() :BaseBattleState(BattleState::CastState) {}
    void EnemyCastUpdate(float dt);
    void PlayerCastUpdate(float dt);
    virtual void OnBattleStateIn()override;
    virtual void OnBattleStateUpdate(float dt) override;
    virtual void OnBattleStateOut() override;
};
