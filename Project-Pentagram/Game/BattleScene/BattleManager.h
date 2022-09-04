#pragma once
#include <vector>
#include "SpellCaster/CasterController.h"

enum class BattleState
{
    SetupState = 0,
    InvokeState,
    ResolveState,
    ResultState
};

class BattleManager
{
private:
    BattleState m_CurrentState = BattleState::SetupState;
    std::vector<CasterController*> m_Casters;
    int m_CurrentCasterIndex = 0;

public:
    void SetBattleState(BattleState state) { m_CurrentState = state; }
    BattleState GetBattleState() { return m_CurrentState; }

    void StartBattle();
    void SwapCaster();
    void EndBattle() { m_CurrentState = BattleState::ResultState;} //TODO

    void AddCaster(CasterController* controller);
    CasterController* GetCurrentCaster() { return m_Casters[m_CurrentCasterIndex]; }
    CasterController* GetNextCaster() { return m_Casters[(m_CurrentCasterIndex + 1) % m_Casters.size()]; }
    
    ~BattleManager();
};
