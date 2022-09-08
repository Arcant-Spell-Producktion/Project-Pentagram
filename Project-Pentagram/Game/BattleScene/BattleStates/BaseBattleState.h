#pragma once
#include "Game/BattleScene/BattleManager.h"

enum class BattleState
{
    SetupState = 0,
    CastState,
    CastConfirmState,
    ResolveState,
    ResultState
};

class BaseBattleState
{
public:
    BattleState StateID;

    BaseBattleState(BattleState id) :StateID(id) {};
    virtual void OnBattleStateIn(BattleManager* currentBattleManager) = 0;
    virtual void OnBattleStateOut() = 0;
};


