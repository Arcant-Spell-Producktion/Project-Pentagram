#pragma once
#include <map>

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

    void SetBattleState(BattleState state)
    {
        BattleState OldState = m_CurrentState;
        m_CurrentState = state;

        m_BattleStates[OldState]->OnBattleStateOut();
        m_BattleStates[m_CurrentState]->OnBattleStateIn(&m_Data);

        std::cout << "\n\t Battle State transition: from " << (int)OldState << " , to "<< (int)m_CurrentState <<"\n\n";
    }
    BaseBattleState* GetBattleStates() { return m_BattleStates[m_CurrentState]; }

    void Init()
    {
        for (auto state : BattleStateModel::GetBattleStates())
        {
            m_BattleStates.emplace(state->StateID, state);
        }

        m_BattleStates[BattleState::SetupState]->OnBattleStateIn(&m_Data);
    }

    void StartBattle();
    void SwapCaster();
    void EndBattle() { m_CurrentState = BattleState::ResultState; } //TODO

    CasterController* GetCurrentCaster() { return m_Data.Casters[m_Data.CurrentCasterIndex]; }
    CasterController* GetNextCaster() { return m_Data.Casters[(m_Data.CurrentCasterIndex + 1) % m_Data.Casters.size()]; }
    void StandbyAllCaster()
    { 
        for (auto caster : m_Data.Casters)
        {
        caster->SetState(CasterState::Idle); 
        caster->GetSpellCaster()->ResetMana();
        }
    }
    
    ~BattleManager();
};
