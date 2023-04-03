#pragma once
#include "Game/BattleScene/BattleSceneData.h"
#include "Game/GameState/BaseGameState.h"

enum class BattleState
{
    SetupState = 0,
    StandbyState,
    CastState,
    ResolveState,
    ResultState
};

class BaseBattleState :public BaseGameState<BattleState>
{
public:
    BaseBattleState(const BattleState id) :BaseGameState(id) {}
    void OnBattleStateIn() override = 0;
    void OnBattleStateUpdate(float dt) override = 0;
    void OnBattleStateOut() override = 0;
};
