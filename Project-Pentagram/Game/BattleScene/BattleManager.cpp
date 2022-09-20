#pragma once
#include "BattleManager.h"

void BattleManager::SetBattleState(BattleState state)
{
    BattleState OldState = m_CurrentState;
    m_CurrentState = state;

    m_BattleStates[OldState]->OnBattleStateOut();
    m_BattleStates[m_CurrentState]->OnBattleStateIn();

    std::cout << "\n\t Battle State transition: from " << (int)OldState << " , to " << (int)m_CurrentState << "\n\n";
}

void BattleManager::StartBattle()
{
    SetBattleState(BattleState::CastState);
}

void BattleManager::SwapCaster()
{
    if (m_Data.GetCurrentCaster()->GetState() == CasterState::Passed && m_Data.GetNextCaster()->GetState() == CasterState::Passed)
    {

        std::cout << "\t GO TO RESOLVE\n";

        SetBattleState(BattleState::ResolveState);
        return;
    }
    m_Data.CurrentCasterIndex = (m_Data.CurrentCasterIndex + 1) % m_Data.Casters.size();
  
    m_Data.GetCurrentCaster()->StartTurn(m_Data.pentragramController->ResetPentagram());
}

BattleManager::~BattleManager()
{
    for(CasterController* cc : m_Data.Casters)
    {
        delete cc;
    }
    m_Data.Casters.clear();

    for (auto statePair: m_BattleStates)
    {
        delete statePair.second;
    }

    m_BattleStates.clear();
}
