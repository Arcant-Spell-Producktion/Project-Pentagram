#pragma once
#include "Game/BattleScene/BattleStates/BaseBattleState.h"

template <typename  STATE>
class IBattleManager
{
public:
    virtual void SetBattleState(STATE state) = 0;

    virtual BaseGameState<STATE>* GetBattleStates() = 0;

    virtual void Init(IGameObjectManager* scene) = 0;

    virtual void StartBattle() = 0;
    virtual void SwapCaster() = 0;
    virtual void EndBattle() = 0;
};