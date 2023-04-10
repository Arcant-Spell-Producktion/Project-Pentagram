#pragma once
#include "Game/BattleScene/BattleSceneData.h"
#include "Game/GameState/BaseGameState.h"

enum class TutorialState
{
    SetupState = 0,
    ExplainState = 1,
    StandbyState = 2,
    CastState = 3,
    ResolveState = 4,
    ResultState = 5
};

class BaseBattleState : public BaseGameState<TutorialState>
{
public:
    BaseBattleState(const TutorialState id) :BaseGameState(id) {}
    void OnBattleStateIn() override = 0;
    void OnBattleStateUpdate(float dt) override = 0;
    void OnBattleStateOut() override = 0;
};


