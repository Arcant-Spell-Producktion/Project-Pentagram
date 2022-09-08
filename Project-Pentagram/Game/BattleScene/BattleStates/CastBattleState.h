#pragma once
#include "BaseBattleState.h"

enum class CastUpdateState
{
    Casting,
    Casted,
};

class CastBattleState : public BaseBattleState
{
public:
    CastBattleState() :BaseBattleState(BattleState::CastState) {}
    virtual void OnBattleStateIn(BattleSceneData* currentBattleData) {
        //BattleManager::GetInstance()->StandbyAllCaster(); 
    }
    virtual void OnBattleStateOut() override {}
};
