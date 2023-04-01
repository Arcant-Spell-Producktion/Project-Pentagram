#pragma once
#include "Game/BattleScene/BattleManager.h"

#include "Game/GameData/RuntimeGameData.h"
#include "Game/GameData/CasterData/CasterStatDatabase.h"
#include "Game/GameData/CasterData/CasterMovesetDatabase.h"

#include "Engine/Audio/AudioController.h"

#include "ExplainTutorialState.h"

#include "Engine/GameStateController.h"

void ExplainTutorialState::OnBattleStateIn()
{
    RuntimeGameData* gameData = RuntimeGameData::GetInstance();
    TutorialNode* currentNode = gameData->Tutorial.GetTutorialNode();

    m_CurrentText = 0;
    m_explainTexts = currentNode->GetTexts();

    m_Texts = GameStateController::GetInstance()->currentScene->CreateObject(new TextBox(m_explainTexts[m_CurrentText]));
    m_Texts->textObject.text = m_explainTexts[m_CurrentText];

    m_Texts->position.y -= 300.0f;
    m_Texts->onClick += [this](Button* button)
    {
        m_CurrentText++;

        if (m_CurrentText >= m_explainTexts.size())
        {
            BattleManager::GetInstance()->SetBattleState(BattleState::StandbyState);
        }
        else
        {
            button->textObject.text = m_explainTexts[m_CurrentText];
        }
    };
}

void ExplainTutorialState::OnBattleStateUpdate(float dt)
{

}

void ExplainTutorialState::OnBattleStateOut()
{
    GameStateController::GetInstance()->currentScene->DeleteObjectByPointer(m_Texts);
    m_Texts = nullptr;
}
