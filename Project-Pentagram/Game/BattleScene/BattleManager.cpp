#pragma once
#include "BattleManager.h"

void BattleManager::SetBattleState(BattleState state)
{
    BattleState OldState = m_CurrentState;

    if (OldState < BattleState::ResultState)
    {
        m_CurrentState = state;

        m_BattleStates[OldState]->OnBattleStateOut();
        m_BattleStates[m_CurrentState]->OnBattleStateIn();
    }

    std::cout << "\n\t Battle State transition: from " << (int)OldState << " , to " << (int)m_CurrentState << "\n\n";
}

void BattleManager::Init(IGameObjectManager* scene)
{
    for (auto state : BattleStateModel::GetBattleStates())
    {
        m_BattleStates.emplace(state->StateID, state);
    }

    Data.Pentagram = new PentragramController(scene);
    Data.Timeline.UI = scene->CreateObject(new TimelineController());
    Data.WillCompare = scene->CreateObject(new WillCompareController());

    m_BattleStates[BattleState::SetupState]->OnBattleStateIn();
}

void BattleManager::StartBattle()
{
    SetBattleState(BattleState::CastState);
}

void BattleManager::SwapCaster()
{
    if (Data.GetCurrentCaster()->GetState() == CasterState::Passed && Data.GetNextCaster()->GetState() == CasterState::Passed)
    {

        std::cout << "\t GO TO RESOLVE\n";

        SetBattleState(BattleState::ResolveState);
        return;
    }
    Data.CurrentCasterIndex = (Data.CurrentCasterIndex + 1) % Data.Casters.size();
  
    Data.GetCurrentCaster()->StartTurn();
    Data.Pentagram->SetPentagramOwner(Data.GetCurrentCaster());
}

void BattleManager::UpdateDisplaySpellDetail(CasterPosition position,CastSpellDetail* spell, bool isMainData, glm::vec3 IconPos)
{
    Data.GetCaster(position)->GetCasterUI()->SetDetail(spell,isMainData,IconPos);
}

BattleManager::~BattleManager()
{
    for(CasterController* cc : Data.Casters)
    {
        delete cc;
    }
    Data.Casters.clear();

    for (auto statePair: m_BattleStates)
    {
        delete statePair.second;
    }

    m_BattleStates.clear();
}
