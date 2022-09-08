#pragma once
#include "BattleManager.h"

void BattleManager::AddCaster(CasterController* controller)
{
    m_Casters.push_back(controller);
}

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
    m_CurrentCasterIndex = (m_CurrentCasterIndex + 1) % m_Casters.size();

    GetCurrentCaster()->StartTurn();

    SetBattleState(BattleState::CastState);
}

BattleManager::~BattleManager()
{
    for(CasterController* cc : m_Casters)
    {
        delete cc;
    }
    m_Casters.clear();

    for (auto statePair: m_BattleStates)
    {
        delete statePair.second;
    }
    m_BattleStates.clear();
}
