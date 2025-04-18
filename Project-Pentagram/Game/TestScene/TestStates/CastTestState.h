#pragma once
#include "Game/BattleScene/BattleStates/BaseBattleState.h"



class CastTestState : public BaseBattleState
{
public:
    enum class CastUpdateState
    {
        Casting,
        Casted,
    };

    CastTestState() :BaseBattleState(BattleState::CastState) {}
    void EnemyCastUpdate(float dt);
    void PlayerCastUpdate(float dt);
    virtual void OnBattleStateIn()override;
    virtual void OnBattleStateUpdate(float dt) override;
    virtual void OnBattleStateOut() override;
};
