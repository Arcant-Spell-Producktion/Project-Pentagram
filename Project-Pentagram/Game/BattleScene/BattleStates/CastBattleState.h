#pragma once
#include "BaseBattleState.h"

class CastBattleState : public BaseBattleState
{
public:
    CastBattleState() :BaseBattleState(BattleState::CastState) {}
    virtual void OnBattleStateIn(BattleManager* currentBattleManager) override { //BattleManager::GetInstance()->StandbyAllCaster(); 
    }
    virtual void OnBattleStateOut() override {}
};
