#pragma once
#include "BaseTutorialState.h"

enum class CastUpdateState
{
    Casting,
    Casted,
};

class CastTutorialState : public BaseTutorialState
{
public:
    CastTutorialState() :BaseTutorialState(TutorialState::CastState) {}
    virtual void OnBattleStateIn()override;
    virtual void OnBattleStateUpdate(float dt) override;
    virtual void OnBattleStateOut() override;
};
