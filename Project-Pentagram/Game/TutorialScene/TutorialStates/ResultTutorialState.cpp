#pragma once
#include "Engine/SceneManager.h"
#include "Game/BattleScene/BattleManager.h"
#include "Game/BattleScene/SpellCaster/PlayerController.h"
#include "Game/GameData/RuntimeGameData.h"
#include "ResultTutorialState.h"

void ResultTutorialState::OnBattleStateIn()
{
    BattleManager& battleManager = BattleManager::GetInstance();
    RuntimeGameData& gameData = RuntimeGameData::GetInstance();
    TutorialNode* currentNode = gameData.Tutorial.GetTutorialNode();

    bool isPlayerAlive = battleManager.Data.GetCaster(CasterPosition::CasterA)->IsAlive();
    battleManager.Data.Pentagram->SetActive(false);
    battleManager.Data.Texts->SetActive(true);

    battleManager.Data.Texts->textObject.text = isPlayerAlive? currentNode->CompleteText : currentNode->RetryText;

    battleManager.Data.Texts->onClick = [this, isPlayerAlive, currentNode](Button* button)
    {
        if (!isPlayerAlive)
        {
            SceneManager::LoadScene(GameState::GS_RESTART);
            return;
        }

        SceneManager::LoadScene(GameState::GS_MENU_SCENE);
    };

}

void ResultTutorialState::OnBattleStateUpdate(float dt)
{
 
}

void ResultTutorialState::OnBattleStateOut()
{

}
