#pragma once
#include "TutorialManager.h"

void TutorialManager::SetBattleState(TutorialState state)
{
    TutorialState OldState = m_CurrentState;

    if (OldState < TutorialState::ResultState)
    {
        m_CurrentState = state;

        m_TutorialStates[OldState]->OnBattleStateOut();
        m_TutorialStates[m_CurrentState]->OnBattleStateIn();
    }

    std::cout << "\n\t Tutorial State transition: from " << (int)OldState << " , to " << (int)m_CurrentState << "\n\n";
}

void TutorialManager::Init(IGameObjectManager* scene)
{
    for (auto state : TutorialStateModel::GetTutorialStates())
    {
        m_TutorialStates.emplace(state->StateID, state);
    }

    Data.Pentagram = new PentragramController(scene);
    Data.Timeline.UI = scene->CreateObject(new TimelineController());
    Data.WillCompare = scene->CreateObject(new WillCompareController());

    m_TutorialStates[TutorialState::SetupState]->OnBattleStateIn();
}

void TutorialManager::StartBattle()
{
    for(auto caster: Data.Casters)
    {
        caster->GetCasterManager()->ResetMana();
    }

    SetBattleState(TutorialState::StandbyState);
}

void TutorialManager::SwapCaster()
{
    if (Data.GetCurrentCaster()->GetState() == CasterState::Passed && Data.GetNextCaster()->GetState() == CasterState::Passed)
    {

        std::cout << "\t GO TO RESOLVE\n";

        SetBattleState(TutorialState::ResolveState);
        return;
    }
    Data.CurrentCasterIndex = (Data.CurrentCasterIndex + 1) % Data.Casters.size();
  
    Data.GetCurrentCaster()->StartTurn();
    Data.Pentagram->SetPentagramOwner(Data.GetCurrentCaster());
}

void TutorialManager::UpdateDisplaySpellDetail(CasterPosition position,CastSpellDetail* spell, bool isMainData, glm::vec3 IconPos)
{
    Data.GetCaster(position)->GetCasterUI()->SetDetail(spell,isMainData,IconPos);
}

TutorialManager::~TutorialManager()
{
    for(CasterController* cc : Data.Casters)
    {
        delete cc;
    }
    Data.Casters.clear();

    for (auto statePair: m_TutorialStates)
    {
        delete statePair.second;
    }

    m_TutorialStates.clear();
}
