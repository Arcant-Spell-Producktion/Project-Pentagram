#pragma once
#include "Game/BattleScene/BattleStates/BaseBattleState.h"

class StandByTutorialState : public BaseBattleState
{
private:
    float Timer = 0.0f;
    float MaxTime = 3.0f;
public:
    StandByTutorialState() :BaseBattleState(BattleState::StandbyState) {}
    virtual void OnBattleStateIn()override;
    virtual void OnBattleStateUpdate(float dt) override;
    virtual void OnBattleStateOut() override;
};
