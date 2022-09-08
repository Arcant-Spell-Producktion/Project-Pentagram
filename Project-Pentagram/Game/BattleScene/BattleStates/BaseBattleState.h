#pragma once
#include "Game/BattleScene/BattleSceneData.h"

enum class BattleState
{
    SetupState = 0,
    CastState,
    ResolveState,
    ResultState
};

class BaseBattleState
{
public:
    BattleState StateID;

    BaseBattleState(BattleState id) :StateID(id) {};
    virtual void OnBattleStateIn(BattleSceneData* currentBattleData) = 0;


    virtual void OnBattleStateOut() = 0;
};


