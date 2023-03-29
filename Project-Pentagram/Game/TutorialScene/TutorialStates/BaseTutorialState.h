#pragma once
#include "Game/BattleScene/BattleSceneData.h"
#include "Game/GameState/BaseGameState.h"

enum class TutorialState
{
    SetupState = 0,
    ExplainState,
    StandbyState,
    CastState,
    ResolveState,
    ResultState
};

class BaseTutorialState : virtual public BaseGameState<TutorialState>
{
public:
    BaseTutorialState(const TutorialState id) :BaseGameState(id) {}
    void OnBattleStateIn() override = 0;
    void OnBattleStateUpdate(float dt) override = 0;
    void OnBattleStateOut() override = 0;
};


