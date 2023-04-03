#pragma once
#include "Game/BattleScene/BattleStates/BaseBattleState.h"



class CastTutorialState : public BaseBattleState
{
public:

    enum class CastUpdateState
    {
        Casting,
        Casted,
    };

    CastTutorialState() :BaseBattleState(BattleState::CastState) {}
    virtual void OnBattleStateIn()override;
    virtual void OnBattleStateUpdate(float dt) override;
    virtual void OnBattleStateOut() override;
};
