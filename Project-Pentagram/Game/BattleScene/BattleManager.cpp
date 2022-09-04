#include "BattleManager.h"

void BattleManager::AddCaster(CasterController* controller)
{
    m_Casters.push_back(controller);
}

void BattleManager::StartBattle()
{
    m_CurrentState = BattleState::InvokeState;
}

void BattleManager::SwapCaster()
{
    if (GetCurrentCaster()->GetState() == CasterState::Passed && GetNextCaster()->GetState() == CasterState::Passed)
    {
        m_CurrentState = BattleState::ResolveState;
        return;
    }
    m_CurrentCasterIndex = (m_CurrentCasterIndex + 1) % m_Casters.size();

    GetCurrentCaster()->StartTurn();
}

BattleManager::~BattleManager()
{
    for(CasterController* cc : m_Casters)
    {
        delete cc;
    }
    m_Casters.clear();
}
