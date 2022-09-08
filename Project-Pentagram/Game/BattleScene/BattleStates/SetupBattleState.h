#pragma once
#include "BaseBattleState.h"

class SetupBattleState : public BaseBattleState
{
public:
    SetupBattleState() :BaseBattleState(BattleState::SetupState) {}
    virtual void OnBattleStateIn(BattleSceneData* currentBattleData) override;
    virtual void OnBattleStateOut() override {}
};
