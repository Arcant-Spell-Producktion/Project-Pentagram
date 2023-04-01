#pragma once
#include "Game/BattleScene/BattleStates/BaseBattleState.h"



template <class STATE>
class IBattleManager
{
public:
    virtual ~IBattleManager() = default;

    virtual void SetBattleState(STATE state) = 0;

    virtual BaseGameState<STATE>* GetBattleStates() = 0;

    virtual void  Init(IGameObjectManager* scene, bool isTutorial = false) = 0;

    virtual void StartBattle(bool isTutorial) = 0;
    virtual void SwapCaster() = 0;
    virtual void EndBattle() = 0;
};