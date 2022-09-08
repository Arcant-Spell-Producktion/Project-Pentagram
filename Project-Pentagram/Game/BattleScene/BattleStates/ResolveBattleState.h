#pragma once
#include "BaseBattleState.h"

class ResolveBattleState : public BaseBattleState
{
public:
    ResolveBattleState() :BaseBattleState(BattleState::ResolveState) {}
    virtual void OnBattleStateIn(BattleSceneData* currentBattleData) override {};
    virtual void OnBattleStateOut() override {}

};
