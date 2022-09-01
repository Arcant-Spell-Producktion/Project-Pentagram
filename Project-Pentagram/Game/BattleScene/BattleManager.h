#pragma once
#include <vector>
#include "SpellCaster/CasterController.h"

enum class BattleState
{
    InvokeState,
    ResolveState,
    ResultState
};

class BattleManager
{
private:
    BattleState m_CurrentState = BattleState::InvokeState;
    std::vector<CasterController*> m_Casters;
    CasterController* m_CurrentCaster = nullptr;

public:
    void SetBattleState(BattleState state) { m_CurrentState = state; }
    BattleState GetBattleState() { return m_CurrentState; }

    void AddCaster();
    CasterController* ChangeNextCaster();
    const CasterController* GetCurrentCaster() { return m_CurrentCaster; }
    ~BattleManager();
};
