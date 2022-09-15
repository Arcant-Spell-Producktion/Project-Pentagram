#pragma once
#include <map>
#include <vector>
#include "Game/BattleScene/BattleSceneData.h"
#include "Game/BattleScene/BattleStates/BattleStateModel.h"
#include "Utilities/Singleton.h"

class BattleManager : public Singleton<BattleManager>
{
private:
    BattleSceneData m_Data;
    BattleState m_CurrentState = BattleState::SetupState;
    std::map<BattleState, BaseBattleState*> m_BattleStates;



public:
    BattleSceneData* GetData() { return &m_Data; }

    void SetBattleState(BattleState state);

    BaseBattleState* GetBattleStates() { return m_BattleStates[m_CurrentState]; }

    void Init()
    {
        for (auto state : BattleStateModel::GetBattleStates())
        {
            m_BattleStates.emplace(state->StateID, state);
        }

        m_BattleStates[BattleState::SetupState]->OnBattleStateIn();
    }

    void StartBattle();
    void SwapCaster();
    void EndBattle() { m_CurrentState = BattleState::ResultState; } //TODO


    ~BattleManager();
};
