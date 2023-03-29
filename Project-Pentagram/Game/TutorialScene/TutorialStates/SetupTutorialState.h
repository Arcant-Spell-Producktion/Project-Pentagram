#pragma once
#include "BaseTutorialState.h"

class SetupTutorialState : public BaseTutorialState
{
public:
    SetupTutorialState() :BaseTutorialState(TutorialState::SetupState) {}
    virtual void OnBattleStateIn()override;
    virtual void OnBattleStateUpdate(float dt) override;
    virtual void OnBattleStateOut() override;
};
