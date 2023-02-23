#pragma once
#include "Game/BattleScene/BattleSceneData.h"

enum class BattleState
{
    SetupState = 0,
    StandbyState,
    CastState,
    ResolveState,
    ResultState
};

class BaseBattleState
{
public:
    BattleState StateID;

    BaseBattleState(BattleState id) :StateID(id) {};
    virtual void OnBattleStateIn() = 0;
    virtual void OnBattleStateUpdate(float dt) = 0;
    virtual void OnBattleStateOut() = 0;
};

 
