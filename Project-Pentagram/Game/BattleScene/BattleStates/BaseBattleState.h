#pragma once
#include "Game/BattleScene/BattleSceneData.h"
#include "Game/BattleScene/BattleStates/BattleState.h"

class BaseBattleState
{
public:
    BattleState StateID;

    BaseBattleState(BattleState id) :StateID(id) {};
    virtual void OnBattleStateIn() = 0;
    virtual void OnBattleStateUpdate(float dt) = 0;
    virtual void OnBattleStateOut() = 0;
};

 
