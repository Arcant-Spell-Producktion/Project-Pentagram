#pragma once
#include <map>
#include <vector>
#include "Game/BattleScene/BattleStates/BattleStateModel.h"
#include "Utilities/Singleton.h"
#include "SpellTimeline/SpellTimeline.h"
#include "SpellCaster/CasterController.h"

class BattleManager : public Singleton<BattleManager>
{
private:
    BattleState m_CurrentState = BattleState::SetupState;
    std::map<BattleState, BaseBattleState*> m_BattleStates;
    int m_CurrentCasterIndex = 0;
    std::vector<CasterController*> m_Casters;
    SpellTimeline m_Timeline;

public:
    void SetBattleState(BattleState state)
    {
        BattleState OldState = m_CurrentState;
        m_CurrentState = state;

        m_BattleStates[OldState]->OnBattleStateOut();
        m_BattleStates[m_CurrentState]->OnBattleStateIn(this);

        std::cout << "\n\t Battle State transition: from " << (int)OldState << " , to "<< (int)m_CurrentState <<"\n\n";
    }
    BaseBattleState* GetBattleStates() { return m_BattleStates[m_CurrentState]; }

    void Init()
    {
        for (auto state : BattleStateModel::GetBattleStates())
        {
            m_BattleStates.emplace(state->StateID,state);
        }

        m_BattleStates[BattleState::SetupState]->OnBattleStateIn(this);
    }

    void StartBattle();
    void SwapCaster();
    void EndBattle() { m_CurrentState = BattleState::ResultState; } //TODO

    SpellTimeline* GetTimeline(){return &m_Timeline;}

    void AddCaster(CasterController* controller);
    CasterController* GetCurrentCaster() { return m_Casters[m_CurrentCasterIndex]; }
    CasterController* GetNextCaster() { return m_Casters[(m_CurrentCasterIndex + 1) % m_Casters.size()]; }
    void StandbyAllCaster()
    { 
        for (auto caster : m_Casters)
        {
        caster->SetState(CasterState::Idle); 
        caster->GetSpellCaster()->ResetMana();
        }
    }
    
    ~BattleManager();
};
