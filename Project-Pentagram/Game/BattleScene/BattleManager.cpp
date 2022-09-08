#pragma once
#include "BattleManager.h"

void BattleManager::StartBattle()
{
    SetBattleState(BattleState::CastState);
}

void BattleManager::SwapCaster()
{
    if (GetCurrentCaster()->GetState() == CasterState::Passed && GetNextCaster()->GetState() == CasterState::Passed)
    {
        SetBattleState(BattleState::ResolveState);
        return;
    }
    m_Data.CurrentCasterIndex = (m_Data.CurrentCasterIndex + 1) % m_Data.Casters.size();

    GetCurrentCaster()->StartTurn();

    SetBattleState(BattleState::CastState);
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
