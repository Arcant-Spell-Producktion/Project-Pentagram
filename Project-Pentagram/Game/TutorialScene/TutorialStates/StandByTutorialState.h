#pragma once
#include "BaseTutorialState.h"

class StandByTutorialState : public BaseTutorialState
{
private:
    float Timer = 0.0f;
    float MaxTime = 3.0f;
public:
    StandByTutorialState() :BaseTutorialState(TutorialState::StandbyState) {}
    virtual void OnBattleStateIn()override;
    virtual void OnBattleStateUpdate(float dt) override;
    virtual void OnBattleStateOut() override;
};
