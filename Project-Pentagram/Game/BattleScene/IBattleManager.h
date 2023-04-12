#pragma once
#include "Game/BattleScene/BattleStates/BaseBattleState.h"

enum class BattleMode
{
    Battle,
    Test,
    Tutorial
};

template <class STATE>
class IBattleManager
{
public:
    

    virtual ~IBattleManager() = default;

    virtual void SetBattleState(STATE state) = 0;

    virtual BaseGameState<STATE>* GetBattleStates() = 0;

    virtual void  Init(IGameObjectManager* scene, BattleMode mode = BattleMode::Battle) = 0;

    virtual void StartBattle(BattleMode mode) = 0;
    virtual void SwapCaster() = 0;
    virtual void EndBattle() = 0;
};