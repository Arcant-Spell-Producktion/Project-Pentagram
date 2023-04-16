#pragma once
#include "Game/BattleScene/BattleManager.h"

#include "Game/GameData/RuntimeGameData.h"
#include "Game/GameData/CasterData/CasterStatDatabase.h"

#include "ExplainTutorialState.h"

#include "Engine/GameStateController.h"

void ExplainTutorialState::UpdateEvent()
{
    m_Texts->textObject.text = m_TutorialStep[m_CurrentEvent].TutorialText;
    for (TutorialObjectEvent e : m_TutorialStep[m_CurrentEvent].ObjectEvents)
    {
        if (e.Obj == MainObjectEnum::Null && e.Type == TutorialEventType::Focus)
        {
            GameStateController::GetInstance()->currentScene->UnFocusObject();
            continue;
        }

        if (e.Obj >= MainObjectEnum::Pentagram)
        {
            if (e.Type == TutorialEventType::Toggle)
            {
                BattleManager::GetInstance()->Data.Pentagram->SetPentagramActive(e.Obj, e.Active);
            }

            if (e.Type == TutorialEventType::Focus)
            {
                GameStateController::GetInstance()->currentScene->FocusObject(BattleManager::GetInstance()->Data.Pentagram->GetPentagramObject(e.Obj));
            }
        }
    }
}

void ExplainTutorialState::OnTextClick()
{

    m_CurrentEvent++;

    if (m_CurrentEvent >= m_TutorialStep.size())
    {
        BattleManager::GetInstance()->SetBattleState(BattleState::CastState);
        GameStateController::GetInstance()->currentScene->UnFocusObject();
    }
    else
    {
        UpdateEvent();
    }
}

void ExplainTutorialState::OnBattleStateIn()
{
    RuntimeGameData* gameData = RuntimeGameData::GetInstance();
    TutorialNode* currentNode = gameData->Tutorial.GetTutorialNode();
    BattleManager* bm = BattleManager::GetInstance();

    bm->Data.Pentagram->SetActive(true);
    bm->Data.Pentagram->SetPentagramOwner(bm->Data.GetCurrentCaster());
    bm->Data.Pentagram->SetPentagramData(currentNode->PlayerStartSpell);

    m_TutorialStep = currentNode->GetTutorialEvents();
    m_CurrentEvent = 0;

    m_Texts = GameStateController::GetInstance()->currentScene->CreateObject(new TextBox(m_TutorialStep[m_CurrentEvent].TutorialText));
    bm->Data.Texts = m_Texts;
    UpdateEvent();

    m_Texts->position.y -= 300.0f;
    m_Texts->onClick += [this, bm](Button* button)
    {
        OnTextClick();
    };
}

void ExplainTutorialState::OnBattleStateUpdate(float dt)
{

}

void ExplainTutorialState::OnBattleStateOut()
{
    GameStateController::GetInstance()->currentScene->UnFocusObject();
    m_Texts->SetActive(false);
}
