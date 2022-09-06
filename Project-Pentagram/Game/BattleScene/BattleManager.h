#pragma once
#include <vector>
#include "Utilities/Singleton.h"
#include "SpellTimeline/SpellTimeline.h"
#include "SpellCaster/CasterController.h"

enum class BattleState
{
    SetupState = 0,
    CastState,
    CastConfirmState,
    ResolveState,
    ResultState
};

class BattleManager : public Singleton<BattleManager>
{
private:
    BattleState m_CurrentState = BattleState::SetupState;
    SpellTimeline m_Timeline;
    std::vector<CasterController*> m_Casters;
    int m_CurrentCasterIndex = 0;

public:
    void SetBattleState(BattleState state)
    {
        m_CurrentState = state;
        std::cout << "\n\t Battle State: " << (int)m_CurrentState << "\n\n";
    }
    BattleState GetBattleState() { return m_CurrentState; }

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
