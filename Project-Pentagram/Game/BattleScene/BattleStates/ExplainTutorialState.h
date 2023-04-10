#pragma once
#include "BaseBattleState.h"

class ExplainTutorialState : public BaseBattleState
{
public:
    ExplainTutorialState() :BaseBattleState(BattleState::ExplainState) {}
    virtual void OnBattleStateIn()override;
    virtual void OnBattleStateUpdate(float dt) override;
    virtual void OnBattleStateOut() override;
};
