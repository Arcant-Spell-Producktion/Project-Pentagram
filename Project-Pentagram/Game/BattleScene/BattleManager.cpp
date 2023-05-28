#pragma once
#include "BattleManager.h"

#include "Game/TestScene/TestStates/TestStateModel.h"
#include "Game/TutorialScene/TutorialStates/TutorialStateModel.h"

void BattleManager::SetBattleState(BattleState state)
{
    BattleState OldState = m_CurrentState;

    if (OldState < BattleState::ResultState)
    {
        m_CurrentState = state;

        // Use in checking condition for Toggle PentagramUI
        Data.Timeline.UI->SetCurrentState(state);

        m_BattleStates[OldState]->OnBattleStateOut();
        m_BattleStates[m_CurrentState]->OnBattleStateIn();
    }

    std::cout << "\n\t Battle State transition: from " << (int)OldState << " , to " << (int)m_CurrentState << "\n\n";
}

void BattleManager::Init(IGameObjectManager* scene, Element::Type stageElement, BattleMode mode)
{
    Data.Stage = scene->CreateObject(new StageObject(stageElement));

    Data.Pentagram = new PentragramController(scene);
    
    Data.Timeline.UI = scene->CreateObject(new TimelineController());
    Data.Timeline.UI->SetPentragramControllerReference(Data.Pentagram);

    Data.GameOverUI = scene->CreateObject(new GameOverUI());

    Data.WillCompare = scene->CreateObject(new WillCompareController());

    std::vector <BaseBattleState*> states;
    switch (mode) {
    case BattleMode::Battle:
        states = BattleStateModel::GetBattleStates();
        break;
    case BattleMode::Test:
        states = TestStateModel::GetTestStates();
        break;
    case BattleMode::Tutorial:
        states = TutorialStateModel::GetTutorialStates();
        break;
    }
    for (auto state : states)
    {
        m_BattleStates.emplace(state->StateID, state);
    }

    m_BattleStates[BattleState::SetupState]->OnBattleStateIn();
}

void BattleManager::StartBattle(BattleMode mode)
{
    for(auto caster: Data.Casters)
    {
        if(mode == BattleMode::Battle)caster->GetCasterManager()->ResetMana();
    }

    SetBattleState(BattleState::StandbyState);
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

void BattleManager::Free()
{
    for (CasterController* cc : Data.Casters)
    {
        delete cc;
    }
    Data.Casters.clear();

    for (auto statePair : m_BattleStates)
    {
        delete statePair.second;
    }

    m_BattleStates.clear();

    m_CurrentState = BattleState::SetupState;
    Data = BattleSceneData();

    Singleton::Free();
}